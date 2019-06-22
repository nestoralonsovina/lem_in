// Model movement of ants for every turn

var colorIndex = 0;
var counterText = d3.select("#counter")

function sleep (ms) {
    return new Promise(resolve => setTimeout(resolve, ms));
}

function updateTurnProgressCounter(reset)
{
        if (!reset)
                turnProgressCounter += 1;
        counterText.text(turnProgressCounter + "/" + sourceCapacity);
}

function colorLink (source, target, color, turnDuration) {

        d3.selectAll("line")
                .filter((d) => {return ((d.target.name == target.datum().name &&
                                        d.source.name == source.datum().name) ||
                                        (d.source.name == target.datum().name &&
                                        d.target.name == source.datum().name))})
                .transition()
                        .delay(turnDuration / 4)
                        .duration(turnDuration / 1.1)
                        .style("stroke", color)
                        .style("stroke-opacity", 1);
}

function updatePathColor(source, target)
{
        // If no color has been assigned to starting node of a path, assign it

        if (!source.attr("pathcolor") && !target.attr("pathcolor"))
        {
            if (source.datum().type == 0)
                    source.attr("pathcolor", color_array[colorIndex]);
            else
                    target.attr("pathcolor", color_array[colorIndex]);

            if (colorIndex < color_array.length)
                    colorIndex++;
            else
                    colorIndex = 0;
        }

        // Else update path with color

        else
        {
            if (source.attr("pathcolor") && source.datum().type == 0)
            {
                target.attr("pathcolor", source.attr("pathcolor"));
                return (source.attr("pathcolor"));
            }
            else
            {
                source.attr("pathcolor", target.attr("pathcolor"));
                return (target.attr("pathcolor"));
            }
        }
}

function drawMoves (turnGroup, turnArray, turnDuration) {

    for (var j = 0; j < turnArray.length; j++) {

        source = d3.select("#" + turnArray[j].source);
        target = d3.select("#" + turnArray[j].target);
        
        color = updatePathColor(source, target);

        var circleMove = turnGroup.append("circle")
                                        .attr("class", "ant")
                                        .attr("cx", source.attr("cx"))
                                        .attr("cy", source.attr("cy"))
                                        .attr("r", nodeRadius * 3)
                                        .attr("fill", "white");

        circleMove.transition()
                        .duration(turnDuration)
                        .attr("cx", target.attr("cx"))
                        .attr("cy", target.attr("cy"));
        
        if (source.datum().type == 2 || target.datum().type == 2)
            updateTurnProgressCounter(0);
        
        colorLink(source, target, color, turnDuration);
    }
  }

var turnDuration = 500;
var turnProgressCounter = 0;

async function runTurns () {

        turnProgressCounter = 0;
        updateTurnProgressCounter(1);

        preventOtherEvents = true;

	// Create new group for displaying moves
        var turnGroup = g.append("g")
		        .attr("id", "turn");

	// Draw turn data behind nodes and on top of links (there's probably a better way to do this)
        d3.selectAll(".links").lower();

	// Stop simulation
        simulation.stop();

	// Display all moves in order
        for (var i = 0; i < turns_data.length; i++)
	{
            drawMoves(turnGroup, turns_data[i], turnDuration);
            await(sleep(turnDuration + 50));
            d3.selectAll(".ant").remove();
        }

        preventOtherEvents = false;
}
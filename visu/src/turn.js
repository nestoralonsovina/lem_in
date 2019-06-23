// Add drag capabilities  

let preventOtherEvents = false;

var drag_handler = d3.drag()
	.on("start", drag_start)
	.on("drag", drag_drag)
	.on("end", drag_end)	
	.filter(() => {return !preventOtherEvents});

drag_handler(node);

// Drag functions

function drag_start(d) {

	if (!d3.event.active) simulation.alphaTarget(0.6).restart();
	d.fx = d.x;
	d.fy = d.y;

}

function drag_end(d) {

	//    if (!d3.event.active) simulation.alphaTarget(0);
	if (!d3.event.active) simulation.stop();
	d.fx = d.x;
	d.fy = d.y;

}

// Makes sure you can't drag the circle outside the box

function drag_drag(d) {

	d.fx = d3.event.x;
	d.fy = d3.event.y;

}

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
		.delay(turnDuration / 5)
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
			.attr("r", nodeRadius * 5)
			.attr("fill", "firebrick");

		circleMove.transition()
			.duration(turnDuration)
			.attr("cx", target.attr("cx"))
			.attr("cy", target.attr("cy"));

		if (source.datum().type == 2 || target.datum().type == 2)
			updateTurnProgressCounter(0);

		colorLink(source, target, color, turnDuration);
	}
}

let turnDuration = 400,
	turnProgressCounter = 0;

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

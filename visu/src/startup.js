function launchTurnsButton() {
    if (!preventOtherEvents)
        runTurns();
}

// Get svg size and hangle resizing

var svg = document.getElementById("viz"),
	html = document.getElementsByTagName("html")[0],
	svg_size = () => {
	svg.setAttribute("width", html.clientWidth - 30);
	svg.setAttribute("height", html.clientHeight - 30);
}

window.addEventListener('resize', svg_size);
svg_size();

// Create svg canvas

var svg = d3.select("svg"),
	width = +svg.attr("width"),
	height = +svg.attr("height"),
	small_map = nodes_data.length <= 100;

// Add encompassing group for the zoom

var g = svg.append("g")
	.attr("class", "everything");

var lw = nodes_data.length >= 1000 ? 10 : "10rem";
var nodeRadius = small_map ? 5 : 25;
var emphasizedNodeRadius = small_map ? "5rem" : "55rem";

// Draw link lines

var link = g.append("g")
	.attr("class", "links")
	.selectAll("line")
	.data(links_data)
	.enter()
	.append("line")
	.attr("stroke-width",  lw) // default 2
	.style("stroke", "lightgrey");

// Draw node circles

var node = g.append("g")
	.attr("class", "nodes")
	.selectAll("circle")
	.data(nodes_data)
	.enter()
	.append("circle")
	.attr("id", d => {return d.name})
	.attr("r", getCircleRadius)
	.attr("fill", circleColour)

var sourceNode = d3.selectAll("circle")
	.filter((d) => {return (d.type == 1)})
	.raise();

var sinkNode = d3.selectAll("circle")
	.filter((d) => {return (d.type == 2)})
	.raise();

// Get circle color from node data

function getCircleRadius(d)
{
	if (d.type != 0)
		return (emphasizedNodeRadius);
	else
		return (nodeRadius);
}

function circleColour(d)
{
	if (d.type == 1)
		return "tomato";
	else if (d.type == 2)
		return "black";
	else
		return ("lightblue");
}

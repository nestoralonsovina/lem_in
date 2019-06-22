// Add drag capabilities  

var preventOtherEvents = false;

var drag_handler = d3.drag()
	.on("start", drag_start)
	.on("drag", drag_drag)
    .on("end", drag_end)	
    .filter(() => {return !preventOtherEvents});
	
drag_handler(node);

// Drag functions

function drag_start(d) {

    if (!d3.event.active) simulation.alphaTarget(0.3).restart();
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
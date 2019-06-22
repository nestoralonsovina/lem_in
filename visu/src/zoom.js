var root = d3.select("svg")

var zoom_handler = d3.zoom()
	.on("zoom", zoom_actions);

var zoom_disable = d3.zoom()
	.on("zoom", null);

function zoom_actions(){
	g.attr("transform", d3.event.transform);
}

zoom_handler(svg);

function zoomFit(transitionDuration) {

	var bounds = root.node().getBBox();
	var parent = root.node().parentElement;
	var fullWidth = parent.clientWidth || parent.parentNode.clientWidth,
		fullHeight = parent.clientHeight || parent.parentNode.clientHeight;
	var width = bounds.width,
		height = bounds.height;
	var midX = bounds.x + width / 2,
		midY = bounds.y + height / 2;
	if (width == 0 || height == 0) return; // nothing to fit
	var scale = 0.85 / Math.max(width / fullWidth, height / fullHeight);
	var translate = [fullWidth / 2 - scale * midX, fullHeight / 2 - scale * midY];

	var transform = d3.zoomIdentity
		.translate(translate[0], translate[1])
		.scale(scale);

	root
		.transition()
		.duration(transitionDuration || 0) // milliseconds
		.call(zoom_handler.transform, transform);
}

zoomFit(0);
zoom_disable(svg);

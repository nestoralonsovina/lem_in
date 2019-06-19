sigma.utils.pkg('sigma.canvas.edges');
sigma.canvas.edges.t = function(edge, source, target, context, settings) {
	var color = edge.color,
		prefix = settings('prefix') || '',
		edgeColor = settings('edgeColor'),
		defaultNodeColor = settings('defaultNodeColor'),
		defaultEdgeColor = settings('defaultEdgeColor');

	context.strokeStyle = color;
	context.lineWidth = edge[prefix + 'size'] || 1;
	context.beginPath();
	context.moveTo(
		source[prefix + 'x'],
		source[prefix + 'y']
	);
	context.lineTo(
		source[prefix + 'x'],
		target[prefix + 'y']
	);
	context.lineTo(
		target[prefix + 'x'],
		target[prefix + 'y']
	);
	context.stroke();
};

var i,
	s,
	N = xy_len,
	E = tar_len,
	g = {
		nodes: [],
		edges: []
	},
	colors = [
		'#617db4',
		'#f36f31',
		'#c930c7',
		'#cdcbcd',
		'lightblue'
	];

// Generate graph:
for (var i = 0; i < N; i++)
	g.nodes.push({
		id: 'n' + i,
		label: x_y[i].label,
		x: x_y[i].x,
		y: x_y[i].y,
		size: 5,
		color: colors[Math.floor(Math.random() * colors.length)]
	});

for (i = 0; i < E; i++)
	g.edges.push({
		id: 'e' + i,
		source: 'n' + tar[i].source,
		target: 'n' + tar[i].target,
		size: 2,
		type: 't',
		color : 'green'
	});

// Instantiate sigma:
s = new sigma({
	graph: g,
	renderer: {
		container: 'graph-container',
		type: 'canvas'
	}
});

s.startForceAtlas2();
s.refresh();

function eventFire(el, etype){
	if (el.fireEvent) {
		el.fireEvent('on' + etype);
	} else {
		var evObj = document.createEvent('Events');
		evObj.initEvent(etype, true, false);
		el.dispatchEvent(evObj);
	}
}

function myFunction() {
	s.graph.nodes().forEach(function(n) {
		if (n.label == 1)
		{
			n.size = 5;
			n.color = 'black';
			console.log(n);
		}
	});
	s.refresh();
}

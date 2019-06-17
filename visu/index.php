<script src="js/sigma.min.js"></script>
<div id="container">
<?php
include 'parse.php';
$var = get_file();
$pos = json_encode(parse_dic($var));
$target = json_encode(target($var));
?>
  <style>
	#graph-container {
	  top: 0;
	  bottom: 0;
	  left: 0;
	  right: 0;
	  position: absolute;
	}
	button {float:left;}
  </style>
	<div id="graph-container">
		<button onclick="myFunction()">Click me</button>
	</div>
</div>
<script src="./js/worker.js"></script>
<script src="./js/supervisor.js"></script>
<script>
var x_y = <?php echo $pos?>,
	tar = <?php echo $target?>,
	tar_len = tar.length,
	xy_len = x_y.length;

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
		size: 0,
		type: 't'
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
function myFunction() {
i = 0;
while (i < 10)
{

}
s.graph.clear();
s.refresh();
}

// Start the ForceAtlas2 algorithm:

</script>

        { data: { id: 'b' } },
        { data: { id: 'c' } },
        { data: { id: 'd' } },
        { data: { id: 'e' } }

	  edges: [
        { data: { id: 'a"e', weight: 1, source: 'a', target: 'e' } },
        { data: { id: 'ab', weight: 1, source: 'a', target: 'b' } },
        { data: { id: 'be', weight: 1, source: 'b', target: 'e' } },
        { data: { id: 'bc', weight: 1, source: 'b', target: 'c' } },
        { data: { id: 'ce', weight: 1, source: 'c', target: 'e' } },
        { data: { id: 'cd', weight: 1, source: 'c', target: 'd' } },
        { data: { id: 'de', weight: 1, source: 'd', target: 'e' } }
]

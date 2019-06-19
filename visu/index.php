<script src="js/sigma.min.js"></script>
<div id="container">
<?php
include 'parse.php';
$var = get_file();
$pos = json_encode(parse_dic($var));
$target = json_encode(target($var));
file_put_contents('push.json', $pos);
file_put_contents('edges.json', $target);

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
	.h { display:none; }
  </style>
	<div id="graph-container">

		<button   onclick="simu()">Click me</button>
		<button class="h" id="leggo" onclick="myFunction()">Click me</button>
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
	}
	;

// Generate graph:
for (var i = 0; i < N; i++)
	g.nodes.push({
		id: 'n' + i,
		label: x_y[i].label,
		x: x_y[i].x,
		y: x_y[i].y,
		size: 5,
		color: 'lightblue'
	});

for (i = 0; i < E; i++)
	g.edges.push({
		id: 'e' + i,
		source: 'n' + tar[i].source,
		target: 'n' + tar[i].target,
		size: 1,
		type: 't',
		color : 'tomato'
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

function simu() {
i = 0;
while (i < 10)
{
eventFire(document.getElementById('leggo'), 'click');
document.getElementById("leggo").removeEventListener("click", myFunction);
i++;
}	
}


function myFunction() {
	s.graph.nodes().forEach(function(n) {
		if (n.label == 1)
		{
			n.size = 5;
			if (i % 2 == 0)
				n.color = 'lightgrey';
			else if (i % 2 == 1)
				n.color = 'red';
			console.log(n.color);
		}
		else
			n.color = 'lightblue';
		s.refresh();
	});
	s.refresh();
}

</script>

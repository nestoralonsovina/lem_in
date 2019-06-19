<!DOCTYPE html>
<html>
<head>
  <title>Basic sigma.js example</title>
  <style type="text/css">
	body {
	  margin: 0;
	}
	#container {
	  position: absolute;
	  width: 100%;
	  height: 100%;
	}
  </style>
</head>
<body>
  <div id="container">

  <button onclick="myFunction()">Click me</button>
</div>
<?php
include 'parse.php';
$var = get_file();
$pos = json_encode(parse_dic($var));
$target = json_encode(target($var));
file_put_contents('push.json', $pos);
file_put_contents('edges.json', $target);

?>
<script src="js/sigma.min.js"></script>
<script src="./js/worker.js"></script>
<script src="./js/supervisor.js"></script>
<script src="./js/sigma.plugins.animate.js"></script>
<script>
var x_y = <?php echo $pos?>,
	tar = <?php echo $target?>,
	E = tar.length,
	N = x_y.length,
	g = {nodes: [], edges: []},
	i,
s;

// Then, let's add some data to display:
for (var i = 0; i < N; i++)
	g.nodes.push({
	id: 'n' + i,
		label: x_y[i].label,
		x: x_y[i].x,
		y: x_y[i].y,
		size: 5,
		color: '#68cfff'
  });

for (i = 0; i < E; i++)
	g.edges.push({
	id: 'e' + i,
		source: 'n' + tar[i].source,
		target: 'n' + tar[i].target,
  });

	s = new sigma({
	graph: g,
		renderer : {container :	'container', type: 'canvas'}
});

s.startForceAtlas2();
s.refresh();
function myFunction() {
	g.nodes[0].color = '#f36f31';
	s = new sigma({
	graph: g,
		renderer : {container :	'container', type: 'canvas'}
})
	s.refresh();
}
// Finally, let's ask our sigma instance to refresh:
</script>
</body>
</html>

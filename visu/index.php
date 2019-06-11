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
  </style>
  <div id="graph-container">

  <button onclick="myFunction()">Click me</button>
	</div>
</div>
<script src="./js/worker.js"></script>
<script src="./js/supervisor.js"></script>
<script>
/**
 * This is a basic example on how to develop a custom edge renderer. In
 * this example, the renderer will display the edge as a path made of two
 * segments, an horizontal one and a vertical one. To make it just a bit
 * "more readable", I also used the FA2 plugin (but it is actually  still
 * not readable).
 *
 * IMPORTANT: This edge renderer just works with the canvas renderer. If
 * you do want to display images with the WebGL renderer, you will have
 * to develop a specific WebGL edge renderer.
*/
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

// Now, let's use the renderer
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
      '#668f3c',
      '#c6583e',
	  '#b956af',
	  'lightblue',
	  'lightgrey'
    ];

// Generate a random graph:
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
    // IMPORTANT:
    // This works only with the canvas renderer, so the
    // renderer type set as "canvas" is necessary here.
    container: 'graph-container',
    type: 'canvas'
  }
});

function myFunction() {
s.refresh();

}

// Start the ForceAtlas2 algorithm:

s.startForceAtlas2();

</script>

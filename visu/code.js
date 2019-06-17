var xy = get_parse(0),
	tar = get_parse(1),
	xy_len = xy.length,
	tar_len = tar.length,
	nodes = [],
	edges = [],
	position = [],
	i;
for (i = 0; i < xy_len; i++)
	nodes.push({	
		data: { id: xy[i].label },
		position: { x : xy[i].label, y : xy[i].label }
	});
for (i = 0; i < tar_len; i++)
	edges.push({	
		data: { id: tar[i].source + tar[i].target, weight: i, source: tar[i].source, target: tar[i].target } 
	});

var cy = cytoscape({
	container: document.getElementById('cy'),

	boxSelectionEnabled: false,
	autounselectify: true,

	style: cytoscape.stylesheet()
	.selector('node')
	.style({
		'content': 'data(id)'
	})
	.selector('edge')
	.style({
		'curve-style': 'bezier',
		'target-arrow-shape': 'triangle',
		'width': 4,
		'line-color': '#ddd',
		'target-arrow-color': '#ddd'
	})
	.selector('.highlighted')
	.style({
		'background-color': '#61bffc',
		'line-color': '#61bffc',
		'target-arrow-color': '#61bffc',
		'transition-property': 'background-color, line-color, target-arrow-color',
		'transition-duration': '0.5s'
	}),

	elements: {
		nodes,
		edges,
		position
	},

	layout: {
		name: 'breadthfirst',
		directed: true,
		roots: '#a',
		padding: 10
	}
});

var bfs = cy.elements().bfs('#0', function(){}, true);

var i = 0;
var highlightNextEle = function(){
	if( i < bfs.path.length ){
		bfs.path[i].addClass('highlighted');

		i++;
		setTimeout(highlightNextEle, 1000);
	}
};

// kick off first highlight
highlightNextEle();

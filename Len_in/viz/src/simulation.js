// Set up the simulation and add forces

if (!smallMap) {
    sourceNode.datum().fx = -10000; //10 000 is a good value for 'big' map
    sourceNode.datum().fy = -10000;
    sinkNode.datum().fx = 10000;
    sinkNode.datum().fy = 10000;
}

var simulation = d3.forceSimulation()
               .nodes(nodes_data)
               .velocityDecay(0.1);
                              
var link_force =  d3.forceLink(links_data)
                       .id(function(d) { return d.name; })
                       .strength(0.5);
         
var charge_force = d3.forceManyBody()
    			.strength(-1000);  // Default : -100
    
var center_force = d3.forceCenter(width / 2, height / 2);  

simulation
    .force("charge_force", charge_force)
    .force("center_force", center_force)
    .force("links",link_force)

// Add tick instructions: 

simulation.on("tick", tickActions);
simulation.stop();

for (var i = 0; i < 100; i++)
    simulation.tick();

tickActions();

function tickActions() {

    //update circle positions each tick of the simulation 
	
    node
        .attr("cx", function(d) { return d.x; })
        .attr("cy", function(d) { return d.y; });
        
    //update link positions 

    link
        .attr("x1", function(d) { return d.source.x; })
        .attr("y1", function(d) { return d.source.y; })
        .attr("x2", function(d) { return d.target.x; })
        .attr("y2", function(d) { return d.target.y; });

}

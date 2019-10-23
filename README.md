---


---

<h1 id="lem-in">Lem-in</h1>
<p>Project done in group with <a href="https://github.com/allen-soler">Jorge Allen Soler</a>.</p>
<h2 id="graphs-algorithm-project">Graph’s algorithm project</h2>
<p>Subject --&gt; <a href="%5Bhttps://cdn.intra.42.fr/pdf/pdf/6161/lem-in.en.pdf%5D(https://cdn.intra.42.fr/pdf/pdf/6161/lem-in.en.pdf)">Lem-in</a></p>
<p>Some of the constraints that we were imposed:</p>
<ol>
<li>Only START and END nodes can have more than one unit concurrently</li>
<li>After exiting one of those nodes, only one unit can be at the same time in each node.</li>
</ol>
<h3 id="problem">Problem</h3>
<p>With the constraints stated before, and having the number of units to move at the start. The problem is to find the combination of not-overlapping paths (Constraint 1) that will minimise the number of movements needed to move from START to END.</p>
<p>An example of the problem would be:</p>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-TD1gGxX9edweCt0u" width="100%" style="max-width: 424.40625px;" viewBox="0 0 424.40625 216"><g transform="translate(-12, -12)"><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath" style="opacity: 1;"><path class="path" d="M81.48502604166667,97L111.9375,72L136.9375,72" marker-end="url(#arrowhead8637)" style="fill:none"></path><defs><marker id="arrowhead8637" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M70.93344155844156,143L111.9375,197L136.9375,197" marker-end="url(#arrowhead8638)" style="fill:none"></path><defs><marker id="arrowhead8638" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,89.72802522664564L191.21875,120L230.859375,120L270.5,120L295.5,150.27197477335434" marker-end="url(#arrowhead8639)" style="fill:none"></path><defs><marker id="arrowhead8639" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,197L191.21875,197L216.21875,197" marker-end="url(#arrowhead8640)" style="fill:none"></path><defs><marker id="arrowhead8640" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M245.5,197L270.5,197L295.5,178.71068190776506" marker-end="url(#arrowhead8641)" style="fill:none"></path><defs><marker id="arrowhead8641" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,61.28931809223492L191.21875,43L216.21875,43" marker-end="url(#arrowhead8642)" style="fill:none"></path><defs><marker id="arrowhead8642" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M245.5,43L270.5,43L295.5,43" marker-end="url(#arrowhead8643)" style="fill:none"></path><defs><marker id="arrowhead8643" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M324.78125,43L349.78125,43L386.117288961039,97" marker-end="url(#arrowhead8644)" style="fill:none"></path><defs><marker id="arrowhead8644" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M324.78125,168L349.78125,168L376.7669270833333,143" marker-end="url(#arrowhead8645)" style="fill:none"></path><defs><marker id="arrowhead8645" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node" id="1" transform="translate(151.578125,72)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">1</div></foreignObject></g></g></g><g class="node" id="2" transform="translate(310.140625,168)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">2</div></foreignObject></g></g></g><g class="node" id="3" transform="translate(151.578125,197)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">3</div></foreignObject></g></g></g><g class="node" id="4" transform="translate(230.859375,197)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">4</div></foreignObject></g></g></g><g class="node" id="5" transform="translate(230.859375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">5</div></foreignObject></g></g></g><g class="node" id="6" transform="translate(310.140625,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">6</div></foreignObject></g></g></g><g class="node" id="START" transform="translate(53.46875,120)" style="opacity: 1;"><rect rx="0" ry="0" x="-33.46875" y="-23" width="66.9375" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-23.46875,-13)"><foreignObject width="46.9375" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">START</div></foreignObject></g></g></g><g class="node" id="END" transform="translate(401.59375,120)" style="opacity: 1;"><rect rx="0" ry="0" x="-26.8125" y="-23" width="53.625" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-16.8125,-13)"><foreignObject width="33.625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">END</div></foreignObject></g></g></g></g></g></g></svg></div>
<h3 id="parsing">Parsing</h3>
<p>To achieve a good performance in this aspect of the program, we ended up using the combination of an AVL (Auto balanced tree) and hashing, to verify that all the information entered was correct, and that there were no mistakes in it.</p>
<p>To represent the graph we used a linked-list, were every node points to an array where we store all it’s neighbours.</p>
<h3 id="solution">Solution</h3>
<p>In this example depending on the number of ants given there are two different optimal solutions</p>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-rbaKdIzFtHW8AR5p" width="100%" style="max-width: 345.125px;" viewBox="0 0 345.125 62"><g transform="translate(-12, -12)"><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath" style="opacity: 1;"><path class="path" d="M86.9375,43L111.9375,43L136.9375,43" marker-end="url(#arrowhead8662)" style="fill:none"></path><defs><marker id="arrowhead8662" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,43L191.21875,43L216.21875,43" marker-end="url(#arrowhead8663)" style="fill:none"></path><defs><marker id="arrowhead8663" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M245.5,43L270.5,43L295.5,43" marker-end="url(#arrowhead8664)" style="fill:none"></path><defs><marker id="arrowhead8664" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node" id="1" transform="translate(151.578125,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">1</div></foreignObject></g></g></g><g class="node" id="2" transform="translate(230.859375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">2</div></foreignObject></g></g></g><g class="node" id="START" transform="translate(53.46875,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-33.46875" y="-23" width="66.9375" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-23.46875,-13)"><foreignObject width="46.9375" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">START</div></foreignObject></g></g></g><g class="node" id="END" transform="translate(322.3125,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-26.8125" y="-23" width="53.625" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-16.8125,-13)"><foreignObject width="33.625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">END</div></foreignObject></g></g></g></g></g></g></svg></div>
<p>When the number of ants is small.<br>
And the combination of the following two paths is the other solution:</p>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-BDevASPukgi1N53b" width="100%" style="max-width: 424.40625px;" viewBox="0 0 424.40625 62"><g transform="translate(-12, -12)"><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath" style="opacity: 1;"><path class="path" d="M86.9375,43L111.9375,43L136.9375,43" marker-end="url(#arrowhead8686)" style="fill:none"></path><defs><marker id="arrowhead8686" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,43L191.21875,43L216.21875,43" marker-end="url(#arrowhead8687)" style="fill:none"></path><defs><marker id="arrowhead8687" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M245.5,43L270.5,43L295.5,43" marker-end="url(#arrowhead8688)" style="fill:none"></path><defs><marker id="arrowhead8688" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M324.78125,43L349.78125,43L374.78125,43" marker-end="url(#arrowhead8689)" style="fill:none"></path><defs><marker id="arrowhead8689" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node" id="2" transform="translate(310.140625,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">2</div></foreignObject></g></g></g><g class="node" id="3" transform="translate(151.578125,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">3</div></foreignObject></g></g></g><g class="node" id="4" transform="translate(230.859375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">4</div></foreignObject></g></g></g><g class="node" id="START" transform="translate(53.46875,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-33.46875" y="-23" width="66.9375" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-23.46875,-13)"><foreignObject width="46.9375" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">START</div></foreignObject></g></g></g><g class="node" id="END" transform="translate(401.59375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-26.8125" y="-23" width="53.625" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-16.8125,-13)"><foreignObject width="33.625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">END</div></foreignObject></g></g></g></g></g></g></svg></div>
<div class="mermaid"><svg xmlns="http://www.w3.org/2000/svg" id="mermaid-svg-wHHofMo8N3PugpR0" width="100%" style="max-width: 424.40625px;" viewBox="0 0 424.40625 62"><g transform="translate(-12, -12)"><g class="output"><g class="clusters"></g><g class="edgePaths"><g class="edgePath" style="opacity: 1;"><path class="path" d="M86.9375,43L111.9375,43L136.9375,43" marker-end="url(#arrowhead8711)" style="fill:none"></path><defs><marker id="arrowhead8711" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M166.21875,43L191.21875,43L216.21875,43" marker-end="url(#arrowhead8712)" style="fill:none"></path><defs><marker id="arrowhead8712" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M245.5,43L270.5,43L295.5,43" marker-end="url(#arrowhead8713)" style="fill:none"></path><defs><marker id="arrowhead8713" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g><g class="edgePath" style="opacity: 1;"><path class="path" d="M324.78125,43L349.78125,43L374.78125,43" marker-end="url(#arrowhead8714)" style="fill:none"></path><defs><marker id="arrowhead8714" viewBox="0 0 10 10" refX="9" refY="5" markerUnits="strokeWidth" markerWidth="8" markerHeight="6" orient="auto"><path d="M 0 0 L 10 5 L 0 10 z" class="arrowheadPath" style="stroke-width: 1; stroke-dasharray: 1, 0;"></path></marker></defs></g></g><g class="edgeLabels"><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g><g class="edgeLabel" transform="" style="opacity: 1;"><g transform="translate(0,0)" class="label"><foreignObject width="0" height="0"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;"><span class="edgeLabel"></span></div></foreignObject></g></g></g><g class="nodes"><g class="node" id="1" transform="translate(151.578125,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">1</div></foreignObject></g></g></g><g class="node" id="5" transform="translate(230.859375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">5</div></foreignObject></g></g></g><g class="node" id="6" transform="translate(310.140625,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-14.640625" y="-23" width="29.28125" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-4.640625,-13)"><foreignObject width="9.28125" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">6</div></foreignObject></g></g></g><g class="node" id="START" transform="translate(53.46875,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-33.46875" y="-23" width="66.9375" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-23.46875,-13)"><foreignObject width="46.9375" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">START</div></foreignObject></g></g></g><g class="node" id="END" transform="translate(401.59375,43)" style="opacity: 1;"><rect rx="0" ry="0" x="-26.8125" y="-23" width="53.625" height="46"></rect><g class="label" transform="translate(0,0)"><g transform="translate(-16.8125,-13)"><foreignObject width="33.625" height="26"><div xmlns="http://www.w3.org/1999/xhtml" style="display: inline-block; white-space: nowrap;">END</div></foreignObject></g></g></g></g></g></g></svg></div>
<p>This might seem when we only have two possibilities, but our program was required to achieve the best possible<br>
solution even when we have 1000, 2000, n paths. Solving up to 10.000 nodes problems in less than 1 second (which we solved in 0.6s, parsing included).</p>
<p>To solved this problem we approached it like a <strong>Maximum flow, minimum cost</strong> type of problem, which in a simpler situation, an already made algorithm would have directly solved our problem. But the task of modifying an already existing algorithm to supply our needs turned out to not be as simple.</p>
<p>For the constraints,  our final solution was to instead of putting capacities on the edges, as you normally would in a flow problem, we set the capacity of our nodes to be 1. So of two different paths crossing through a node, only the best of them would be taken, not both.<br>
We also used a formula derived from testing to calculate the combination of paths that would best suit our need based on the number of ants that we had.</p>
<pre class=" language-c"><code class="prism  language-c"><span class="token keyword">double</span> <span class="token function">compute_ants</span><span class="token punctuation">(</span>t_paths <span class="token operator">*</span>head<span class="token punctuation">,</span> t_paths <span class="token operator">*</span>cur<span class="token punctuation">,</span> t_graph <span class="token operator">*</span>g<span class="token punctuation">)</span>

<span class="token punctuation">{</span>

	<span class="token keyword">int</span> nb_paths<span class="token punctuation">;</span>

	nb_paths <span class="token operator">=</span> <span class="token function">count_paths</span><span class="token punctuation">(</span>head<span class="token punctuation">)</span><span class="token punctuation">;</span>

	<span class="token keyword">return</span> <span class="token punctuation">(</span><span class="token punctuation">(</span>g<span class="token operator">-&gt;</span>nb_ant <span class="token operator">-</span> <span class="token punctuation">(</span><span class="token punctuation">(</span>nb_paths <span class="token operator">-</span> <span class="token number">1</span><span class="token punctuation">)</span> <span class="token operator">*</span> <span class="token punctuation">(</span>cur<span class="token operator">-&gt;</span>len<span class="token punctuation">)</span>\

		<span class="token operator">-</span> <span class="token punctuation">(</span><span class="token function">sum_lengths</span><span class="token punctuation">(</span>head<span class="token punctuation">)</span> <span class="token operator">-</span> <span class="token punctuation">(</span>cur<span class="token operator">-&gt;</span>len<span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">)</span><span class="token punctuation">)</span> <span class="token operator">/</span> nb_paths<span class="token punctuation">)</span><span class="token punctuation">;</span>

<span class="token punctuation">}</span>
</code></pre>
<h3 id="possible-improvements-that-could-be-made">Possible improvements that could be made</h3>
<ol>
<li>The memory management that we did on this project was not the best, although there are no leaks at the end of the program, in some instances we allocate more memory that what we need to and some of the free’s could be done before the end of the program.</li>
</ol>
<p><em>Instructions to test the program will be added soon, Python 3.x, PHP, gcc and Make are needed to properly run the everything</em></p>
<p><strong>Our final note in this project was 125/100.</strong></p>



function triangulate(pointCloud)
{
    // linear array of triangles' indices
    var triangles_linear = Delaunay.triangulate(pointCloud);
	// reshape triangles in a 3 times k matrix
	return triangles = reshape(triangles_linear , 3);
}


function triangles_to_edges(triangles, pointCloud)
{
    var edge_indices = {};
    var edges = [];

    for(var i = 0; i < triangles.length; i++) {
        var cur_edges = k_combinations(triangles[i] , 2);

        for(var e = 0; e < cur_edges.length; e++) {
            var edge = cur_edges[e];

            if(edge[0] > edge[1]) {
                var tmp = edge[0];
                edge[0] = edge[1];
                edge[1] = tmp;
            }
            var v0 = pointCloud[edge[0]];
            var v1 = pointCloud[edge[1]];
            var length = distance(v0, v1);

            if(edge in edge_indices) {
                edges[edge_indices[edge]].triangles.push(i);
                continue;
            }
            edge_indices[edge] = edges.length;
            edges.push({
                vertices: cur_edges[e],
                triangles: [i],
                length: length
            });

        }
    }
    return edges;
}


function algorithm0(pointCloud){
	// Input a point cloud of n points	{(x_1 , y_1), ..., (x_n , y_n)}
    //var triangles_linear = Delaunay.triangulate(pointCloud);

	// Compute Del(P) of k triangles
    var triangles = triangulate(pointCloud);
    var edges = triangles_to_edges(triangles, pointCloud);

	// compute the edges
	edges.sort(function(a, b) {
        if(a.length < b.length) return 1;
        if(a.length > b.length) return -1;
        return 0;
    });

    var triangleInfo = triangles.map(function(triangle, index) {
        var acuteness = isacute(pointCloud[triangle[0]] , pointCloud[triangle[1]] , pointCloud[triangle[2]]);
        var circumradius = 0;

        if(acuteness)
            circumradius = circum(pointCloud[triangle[0]] , pointCloud[triangle[1]] , pointCloud[triangle[2]]);

        return { acuteness: acuteness, circumradius: circumradius };
    });

    // Find non-shared edges, those belong to external region
    var external_edges = [];
    for(var i = 0; i < edges.length; i++) {
        if(edges[i].triangles.length == 2) continue;
        external_edges.push(i);
    }

    triangles.push(external_edges);
    triangleInfo.push({ acuteness: false, circumradius: 0 });

	// Each node has attribute index (the triangle it is associated with)
	// a birth level in the alpha-graph filtration and its uplinks in the alpha graph
    function CreateNode(index, birth){
        var node = {
                ind: index,     // Index of the triangle
                birth: birth,
                uplink: undefined,  // Uplink pointing towards the root
                live: [],
                height: 1,          // Steps from the root
                bar: undefined};    // Index of region containing trinagle T[ind]
        return node;
    }

    function root(i, nodes)
    {
        while(nodes[i].uplink !== undefined)
            i = nodes[i].uplink;
        return i;
    }

    function dup_array(a) {
        b = [];
        for(var i = 0; i < a.length; i++)
            b.push(a[i]);
        return b;
    }

    function CreateRegion(index, r, death) {
        var region = {
            ind: index,
            birth: r.birth,
            death: death,
            core: dup_array(r.live),       // List of triangles in region
            sup: undefined, // Index of superior region merged with R
            heir: undefined, // Node v adjecent to node u
        };

        for(var i = 0; i < r.live.length; i++) {
            r.live[i].bar = index;
            r.live[i].death = death;
        }

        return region;
    }


    function case2(u, v, nodes, regions) {
        //console.log("Case 2");

        var v_root = nodes[root(v.ind, nodes)];

        u.uplink = v_root.ind;
        u.birth = v_root.birth;

        if(v_root.height == 1) {
            v_root.height = 2;
        }

        if(v.bar !== undefined) {
            var region_index = v.bar;
            regions[region_index].core.push(u);

            u.bar = v.bar;
        } else {
            // console.log("Adding node", u, "to list of live nodes of", v_root);
            v_root.live.push(u);
        }
    }


    function case3(u, v, alpha, nodes, regions)
    {
        var v_root = nodes[root(v.ind, nodes)];
        var u_root = nodes[root(u.ind, nodes)];

        var region_index = regions.length;
        // console.log("Creating region", u_root);
        regions.push(CreateRegion(region_index, u_root, alpha));

        if(v.bar !== undefined) {
            regions[region_index].sup = v.bar;
        } else {
            regions[region_index].heir = v.ind;
            // Remember to update sup(R) using heir(R) after the while loop!
        }

        if(u_root.height <= v_root.height) {
            u_root.uplink = v_root.ind;
            if(u_root.height == v_root.height)
                v_root.height++;
        } else {
            v_root.uplink = u_root.ind;
            // console.log("Changing live nodes", u_root, v_root);
            u_root.live = v_root.live;
            u_root.birth = v_root.birth;
        }
    }

    function case4(u, v , alpha) {
        // both triangles are right-angled
        // 1. set birth(u) = birth(v) = alpha
        // console.log("Case 4");
        // console.log("v:")
        // console.log(v)
        u.birth = alpha;
        v.birth = alpha;
        // uplink(v) = u
        v.uplink = u.ind;
        // height(u) = height(u) = 1
        u.height++;
        // add v to Live(u)
        u.live.push(v);

        //
        // throw "Case 4 is not yet implemented";
    }


    var nodes = triangleInfo.map(function(triangle, index) { return CreateNode(index, triangle.circumradius); });

    var external_node = nodes.length;
    nodes.push(CreateNode(external_node, Infinity));

    for(var i = 0; i < nodes.length; i++)
        nodes[i].live = [ nodes[i] ];

    // Add external region as a "triangle" for non-shared edges
    for(var i = 0; i < external_edges.length; i++)
        edges[external_edges[i]].triangles.push(external_node);

    // set the number of links to 0
    var l = 0;
    var e = -1;
    var k = triangleInfo.length;

    var regions = [];

    // stop when Forest(alpha) becomes a tree
    while(l < k){
        e++;

        if(e >= edges.length) {
            //console.warn("Loop terminated prematurely, forest is not yet a tree... but we ran out of edges!");
            break;
        }

        var edge = edges[e];

        // define alpha
        var alpha = 0.5 * edge.length;

        var u = nodes[edge.triangles[0]];
        var v = nodes[edge.triangles[1]];

        var u_root = nodes[root(u.ind, nodes)];
        var v_root = nodes[root(v.ind, nodes)];

        console.assert(u_root !== undefined, "Root(u) should be defined.");
        console.assert(v_root !== undefined, "Root(v) should be defined.");

        // Case 1
        if(u_root === v_root) {
            //console.log("Case 1", u_root, v_root);
            continue;
        }

        // Case 2a
        if(u_root.birth == 0 && v_root.birth > 0) {
            case2(u, v, nodes, regions);
            l++; continue;
        }

        // Case 2b
        if(v_root.birth == 0 && u_root.birth > 0) {
            case2(v, u, nodes, regions);
            l++; continue;
        }

        // Case 3a
        if(u_root.birth > 0 && v_root.birth >= u_root.birth) {
            case3(u, v, alpha, nodes, regions);
            l++; continue;
        }

        // Case 3b
        if(v_root.birth > 0 && u_root.birth >= v_root.birth) {
            case3(v, u, alpha, nodes, regions);
            l++; continue;
        }

        // Case 4
        if(v_root.birth == 0 && u_root.birth == 0)
            case4(u, v , alpha); l++; continue;

        //console.log("Fell through...", u, v);
    }

    // Create last final (outside region)
    region_index = regions.length;
    regions.push(CreateRegion(region_index, nodes[root(0, nodes)], alpha));

    //console.log("Root of the world", root(0, nodes), nodes[root(0, nodes)]);

    // Fill sup(R)
    for(var i = 0; i < regions.length; i++) {
        regions[i].pers = regions[i].birth - regions[i].death;

        if(regions[i].heir === undefined) continue;

        if(regions[i].sup === undefined) {
            regions[i].sup = nodes[regions[i].heir].bar;

            //console.log("Fixing sup: ", regions[i].sup, i);
        }
    }

    // Sort Map(alpha)
    regions = regions.sort(function(r1, r2) {
        var d = r2.pers - r1.pers;

        if(d < 0) return -1;
        if(d > 0) return 1;

        return 0;
    });

    // Build map old index -> new index
    var map = [];
    for(var i = 0; i < regions.length; i++) {
        map[regions[i].ind] = i;
    }

    //console.log(map);

    // Fixing ind(R), sup(R), bar(n) after sorting
    for(var i = 0; i < regions.length; i++) {
        regions[i].ind = i;
        regions[i].sup = map[regions[i].sup];
                // console.log(i, regions[i]);
    }
    for(var i = 0; i < nodes.length; i++) {
        nodes[i].bar = map[nodes[i].bar];
    }

    for(var i = 0; i < regions.length; i++) {
        //console.log(regions[i]);
        //console.log("969:", regions[i].core.filter(function(c) { return c.ind == 969; }));
    }

    //console.log(nodes[969]);

/*
    var withBars = [];
    console.log("Found", regions.length, "regions");

    for(var i = 0; i < regions.length; i++) {
        var region_nodes = [];
        for(var j = 0; j < regions[i].core.length; j++)
            region_nodes.push(regions[i].core[j].ind);

        console.log("Region", i, "has superior", regions[i].sup, "linked by node", regions[i].heir);

        console.log(" - nodes:", region_nodes.join(", "));

        var with_bar = nodes.filter(function(n) { return n.bar == i; }).map(function(n) { return n.ind; });

        console.log(" - nodes with bar set to region:", with_bar.join(", "));
        withBars.push(with_bar);
    }*/

	return regions;
}


function widestGap(map)
{
    var widest_gap = undefined;

    for(var i = 1 ; i < map.length - 1; i++) {
        var p0 = map[i].birth - map[i].death;
        var p1 = map[i + 1].birth - map[i + 1].death;

        var gap = p0 - p1;

        if(widest_gap == undefined || widest_gap.gap < gap) {
            widest_gap = { 'gap': gap, 'pointsAbove': i};
        }
    }

    return widest_gap;
}


function mSegmentation(map, m)
{
    m = parseInt(m);
    if(m == 0) return [];

    function root(map, i, m) {
        while(i > m && i !== undefined)
            i = map[i].sup;

        return i;
    }

    if(m === undefined)
        m = this.widestGap().pointsAbove;

    var mapPrime = [];

    // Copy the first m-regions
    for(var i = 0; i <= Math.min(m, map.length - 1); i++) {
        mapPrime[i] = {
            'core': []
        };

        Array.prototype.push.apply(mapPrime[i].core, map[i].core);
    }

    // Merge remaining regions
    //i + 3 < 4
    // console.log(m, map.length);
    for(var i = m + 1; i < map.length; i++) {

        var sup = root(map, map[i].sup, m);

        //console.log(i, sup, map[i].sup);
        // console.log("map[i].core:")
        // console.log(map[i].core)
        //
        // console.log("sup: " + sup + " mapPrime[sup].core:")
        // console.log(mapPrime[sup].core)

        Array.prototype.push.apply(mapPrime[sup].core, map[i].core);
    }

    return mapPrime;
}

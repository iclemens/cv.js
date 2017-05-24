function reshape(array , n){
	// reshape a standard array in a list of lists. Each sublist has n elements
	try {
        if(array.length % n !== 0) throw "the number of elements of each sublist should divide the cardinality of the array.";
    }
    catch(err) {
        console.log(err);
    }
    var reshaped = [];
    for(var i = 0; i < array.length; i = i + n){
    	var temp_sub = array.slice(i , i + n )
    	reshaped.push(temp_sub);
    }
    return reshaped
}

function trg_border(triangles , vertices){
	// given an array of triangles (each one a list of three indexes corresponding to vertces)
	// return an array of edges
	var delta_trg = [];
	for(var i = 0; i < triangles.length; i = i+3){
		var cur_bord = [vertices[triangles[i + 0]] , vertices[triangles[i+1]] , vertices[triangles[i+2]]];
		delta_trg.push(cur_bord);
	}
	return delta_trg;
}

function zip(arrays) {
	// equivalent of python's zip
    return arrays[0].map(function(_,i){
        return arrays.map(function(array){return array[i]})
    });
}

function ZeroToNArray(N){
	// create an array of the form [1,2,...,N]
	var array = [];
	for(var i = 0; i < N; i++){
		array.push(i);
	}
	return array;
}

function scale(array , n){
 	// multiply an array by a scalar value
 	var scaled = [];
 	for(var i = 0; i < array.length; i++){
 		scaled.push( n * array[i]);
 	}
 	return scaled
 }

 function compareSecondColumn(a, b) {
 	// sort a n x 2 matrix by the values of its second column
    if (a[1] === b[1]) {
        return 0;
    }
    else {
        return (a[1] < b[1]) ? -1 : 1;
    }
}

function compareSecondColumn_dec(a, b) {
 	// sort a n x 2 matrix by the values of its second column
    if (a[1] === b[1]) {
        return 0;
    }
    else {
        return (a[1] > b[1]) ? -1 : 1;
    }
}

function getMaxOfArray(array) {
	// maximal element of an array of double
  return Math.max.apply(null, array);
}

function computeCentreOfMass(v1,v2,v3){
	// computes the centre of mass of a triangle T = [v1,v2,v3]
	try {
		if(v1.length != 2 || v2.length != 2 ||  v3.length != 2)
			throw "Check your vertices! We are working in dimension 2 at this stage";
        if(compare_vertices(v1 , v2) || compare_vertices(v2 , v3) || compare_vertices(v1 , v3))
        	throw "You are trying to compute the centre of mass of a segment!";
    }
    catch(err) {
        console.log(err);
    }
	var x_c = ( v1[0] + v2[0] + v3[0] ) / 3;
	var y_c = ( v1[1] + v2[1] + v3[1] ) / 3;
	var c = [x_c , y_c];
	return c;
}

//  compute distance
function distance(v1 , v2){
	try {
        if(v1.length !=  v2.length) throw "Points should have the same dimension";
        if(v1.length != 2 || v2.length != 2) throw "We are working in dimension 2 at this stage";
    }
    catch(err) {
        console.log(err);
    }
	var dx = (v1[0]-v2[0]);
	var dy = (v1[1]-v2[1]);
	var dist = Math.sqrt(dx*dx + dy*dy);
	// one could think to avoid the square root to be faster
	// var squareddist = dx*dx + dy*dy; // REM: alpha should be squared in this case!
	return dist
}

function distance_squared(v1, v2) {
    var dx = (v1[0] - v2[0]);
    var dy = (v1[1] - v2[1]);

    return dx * dx + dy * dy;
}

function distance_array(points){
	// compute the distance of every (non-repeated) pair in points
	var distances = [];
	n = points.length;
	for(i = 0; i < n; i++){
   		for(j = i + 1; j < n; j++){
      		dist = distance(points[i] , points[j]);
      		distances.push(dist);
   		}
	}
	return distances
}

function distance_squared_array(points) {
	// compute the distance of every (non-repeated) pair in points
	var distances = [];
	n = points.length;
	for(i = 0; i < n; i++){
   		for(j = i + 1; j < n; j++){
      		dist = distance_squared(points[i] , points[j]);
      		distances.push(dist);
   		}
	}
	return distances
}


function isacute(v1,v2,v3){
	// check if a triangle is acute
	var dist = distance_squared_array([v1,v2,v3]);
	var a = dist[0];
	var b = dist[1];
	var c = dist[2];

	return a + b > c && b + c > a && a + c > b;
}


function circum(v1,v2,v3){
	// compute the circumradius of a triangle
	var dist = distance_array([v1,v2,v3]);
	var a = dist[0];
	var b = dist[1];
	var c = dist[2];
	// semiperimeter
	var s = ( a + b + c ) / 2;
	var n = a * b * c;
	var d = 4 * Math.sqrt( s * ( a + b - s ) * ( a + c - s ) * ( b + c - s ) );
	// circumradius
	var r = n / d;
	return r
}

function nonacute(v1,v2,v3){
	// compute the length of edges of a triangles and
	// return half the length of the maximal one
	var dist = distance_array([v1,v2,v3]);
	var a = dist[0];
	var b = dist[1];
	var c = dist[2];
	var r = Math.max(a,b,c);

	var r = r/2;
	return r
}

function maximalEdge([ind1,ind2,ind3]){
	// compute the length of edges of a triangles given the indices of the vertices
	// return the maximal edge (couple of indices)
	var v1 = vertices[ind1];
	var v2 = vertices[ind2];
	var v3 = vertices[ind3];
	var dist = distance_array([v1,v2,v3]);
	// [v1,v2]
	var a = dist[0];
	// [v1,v3]
	var b = dist[1];
	// [v2,v3]
	var c = dist[2];

	// possible pairings
	ed = [[ind1,ind2] , [ind1,ind3] , [ind2,ind3]];

	var r = Math.max(a,b,c);
	var ed_length = [a,b,c];
	var ind = ed_length.indexOf(r);

	var	max_edge = ed[ind];

	return max_edge
}

function k_combinations(set, k) {
	// compute combinations
	var i, j, combs, head, tailcombs;

	if (k > set.length || k <= 0) {
		return [];
	}

	if (k == set.length) {
		return [set];
	}

	if (k == 1) {
		combs = [];
		for (i = 0; i < set.length; i++) {
			combs.push([set[i]]);
		}
		return combs;
	}
	combs = [];
	for (i = 0; i < set.length - k + 1; i++) {
		head = set.slice(i, i+1);
		tailcombs = k_combinations(set.slice(i + 1), k - 1);
		for (j = 0; j < tailcombs.length; j++) {
			combs.push(head.concat(tailcombs[j]));
		}
	}
	return combs;
}


function getUnique(array) {
   var u = {}, a = [];
   for(var i = 0, l = array.length; i < l; ++i){
      if(u.hasOwnProperty(array[i])) {
         continue;
      }
      a.push(array[i]);
      u[array[i]] = 1;
   }
   return a;	
}

function compare_vertices(v1 , v2){
	// return true if two points are equal
	var cmp = false;
	if(v1[0] === v2[0] && v1[1] === v2[1]){
		cmp = true;
	}
	return cmp
}

function compare_edges_ind(e1 , e2){
// takes two unoriented edges and compares them
var cmp = false;
	if(e1[0] === e2[0] && e1[1] === e2[1] || e1[0] === e2[1] && e1[1] === e2[0]){
		cmp = true;
	}
	return cmp;
}

function indexOfEdge(e , array){
	// as indexOf for an array of edges' indices
	var ind = -1;
	for(var i = 0; i < array.length; i++){
		var cur_e = array[i];
		if(compare_edges_ind(e , cur_e)){
			ind = i;
		}
	}
	return ind;
}

function compare_triangle_ind(ind_tr1 , ind_tr2){
	// take a triangle of the form ind_tr1 = [i1,j1,k1] and
	// compare it with ind_tr2
	var sharedEdges = [];
	edges1 = k_combinations(ind_tr1,2);
	edges2 = k_combinations(ind_tr2,2);
	for(var i = 0; i < edges1.length; i++){
		for(var j = 0; j < edges2.length; j++){
			if( compare_edges_ind( edges1[i] , edges2[j] ) ){
				sharedEdges = edges1[i];
			}
		}
	}
	return sharedEdges;
}


function compare_edges( e1 , e2){
	// return true if two unoriented edges have the same boundary
	// edge 1
	var v1s = e1[0];
	var v1e = e1[1];
	// edge 2
	var v2s = e2[0];
	var v2e = e2[1]
	// compare them
	var cmp_ed = false;
	if( compare_vertices(v1s , v2s) && compare_vertices(v1e , v2e) || compare_vertices(v1s , v2e) && compare_vertices(v1e , v2s) ){
		cmp_ed = true;
	}
	return cmp_ed;
}

function compare_edges_array(e , edges){
	// compare a single edge with a list, return true if it already appears in the list.
	if(edges.length > 0){
		for(var i = 0; i < edges.length; i++){
			var isin = false;
			var cur_e = edges[i];
			if(compare_edges(e , cur_e) === true){
				return true;
				break;
			}

		}
	}
	return false
}

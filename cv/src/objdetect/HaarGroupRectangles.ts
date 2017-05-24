/**
 * Returns true if rectangles show enough overlap.
 */
function similarRects(r1: number[], r2: number[], eps: number): boolean
{
    var delta = eps * (Math.min(r1[2], r2[2]) + Math.min(r1[3], r2[3])) * 0.5;
    
    return Math.abs(r1[0] - r2[0]) <= delta &&
            Math.abs(r1[1] - r2[1]) <= delta &&
            Math.abs(r1[0] + r1[2] - r2[0] - r2[2]) <= delta &&
            Math.abs(r1[1] + r1[3] - r2[1] - r2[3]) <= delta;
}

/**
 * Cluster connected rectangles
 */
function partitionRects(rects: number[][], eps: number): number[]
{
    var N: number = rects.length;
    var nodes: number[] = new Array(N * 2);
    var PARENT: number = 0;
    var RANK: number = N;
    
    for(let i: number = 0; i < N; i++) {
        nodes[PARENT + i] = -1;
        nodes[RANK + i] = 0;
    }
    
    for(let i: number = 0; i < N; i++) {
        var root = i;
        while(nodes[PARENT + root] >= 0)
            root = nodes[PARENT + root];
        
        for(var j = 0; j < N; j++) {
            if(i == j || !similarRects(rects[i], rects[j], eps))
                continue;
            
            var root2 = j;
            while(nodes[PARENT + root2] >= 0)
                root2 = nodes[PARENT + root2];
            
            if(root2 != root) {
                var rank = nodes[RANK + root];
                var rank2 = nodes[RANK + root2];
                
                if(rank > rank2) {
                    nodes[PARENT + root2] = root;
                } else {
                    nodes[PARENT + root] = root2;
                    nodes[RANK + root2] += (rank == rank2)?1:0; 
                    root = root2;
                }
                
                var k = j;
                var parent;
                while((parent = nodes[PARENT + k]) >= 0) {
                    nodes[PARENT + k] = root;
                    k = parent;
                }
                
                var k = i;
                var parent;
                while((parent = nodes[PARENT + k]) >= 0) {
                    nodes[PARENT + k] = root;
                    k = parent;
                }
            }
        }
    }
    
    var labels: number[] = new Array(N + 1);
    var nclasses: number = 0;
    
    for(let i: number = 0; i < N; i++) {
        var root = i;
        while(nodes[PARENT + root] >= 0) 
            root = nodes[PARENT + root];
        
        if(nodes[RANK + root] >= 0) {
            nodes[RANK + root] = -(nclasses + 1);
            nclasses++;
        }
        labels[i] = Math.abs(-(nodes[RANK + root] + 1));
    }

    if(N == 0)
        labels[N] = 0;
    else
        labels[N] = nclasses;

    return labels;
}


/**
 * Cluster rectangles
 */
export function groupRectangles(rects: number[][], eps?: number, groupThreshold?: number): number[][]
{
    if(eps === undefined)
        eps = 0.2;
        
    if(groupThreshold === undefined)
        groupThreshold = 1;
    
    var labels = partitionRects(rects, eps);
    var N = labels[labels.length - 1];
            
    // Initialize "clsrects" array
    var clsrects = new Array(N);
    for(let cls: number = 0; cls < clsrects.length; cls++) {
        clsrects[cls] = [0, 0, 0, 0, 0];
    }

    // Loop over labels, computing sum of x, y, w, and h per class        
    // Also count number of labels per class
    for(let i: number = 0; i < rects.length; i++) {
        let cls: number = labels[i];
        
        var weight = 1;
        
        // If rectangle contains weight, use it instead
        if(rects[i].length == 5)
            weight = rects[i][4];
        
        //console.log(cls, clsrects, rects);
        clsrects[cls][0] += (weight * rects[i][0]);
        clsrects[cls][1] += (weight * rects[i][1]);
        clsrects[cls][2] += (weight * rects[i][2]);
        clsrects[cls][3] += (weight * rects[i][3]);
        clsrects[cls][4] += weight;         
    }

    // Scale each class rectangle by 1/numlabels
    for(let cls: number = 0; cls < N; cls++) {
        clsrects[cls][0] /= clsrects[cls][4];
        clsrects[cls][1] /= clsrects[cls][4];
        clsrects[cls][2] /= clsrects[cls][4];
        clsrects[cls][3] /= clsrects[cls][4];            
    }
    
    // Loop over classes
    var objects = [];
    
    for(let i: number = 0; i < N; i++) {
        var r1: number[] = rects[i];
        
        var j: number = 0;
        for(j = 0; j < N; j++) {
            var r2 = rects[j]

            if(i == j || r2[4] <= groupThreshold) continue;
            
            var dx = r2[2] * eps;
            var dy = r2[3] * eps;
            
            if(r1[0] >= r2[0] - dx &&
                r1[1] >= r2[1] - dy &&
                r1[0] + r1[2] <= r2[0] + r2[2] + dx &&
                r1[1] + r1[3] <= r2[1] + r2[3] + dy &&
                (r2[4] > Math.max(3, r1[4]) || r1[4] < 3))
                break;
        }
        
        if(j == N) {
            objects.push(r1);
        }
    }

    return objects;    
}
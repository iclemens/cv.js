
import {FAST} from './FAST';
import {Keypoint} from '../core/Keypoint'
import {Image} from '../core/Image';

export class AGAST
{
    _fast = new FAST();
    _nms: boolean = false;
    
    // Getter and setter functions
    get T(): number { return this._fast.T; }
    set T(T: number) { this._fast.T = T; }
    
    get S(): number { return this._fast.S; }
    set S(S: number) { this._fast.S = S; }
    
    get mask(): number { return this._fast.mask; }
    set mask(mask: number) { this._fast.mask = mask; }
    
    get nms(): boolean { return this._nms; }
    set nms(nms: boolean) { this._nms = nms; }
    
    get subpixel(): boolean { return this._fast.subpixel; }
    set subpixel(subpixel: boolean) { this._fast.subpixel = subpixel; }
    
    
    constructor()
    {
    }
            
    
    getScores(image: Image) {
        this._fast.nms = false;
        return this._fast.getScores(image);
    }
    
    
    getFeatures(image: Image): Keypoint[] 
    {
        this._fast.nms = false;
        var input: Keypoint[] = this._fast.getFeatures(image);
        
        if(!this.nms) return input;

        var nmsFlags: number[] = [];
        for(var i = 0; i < input.length; i++)
            nmsFlags[i] = -1;
                    
        var lastRow = 0;
        var nextLastRow = 0;
        var lastRowInd = 0;
        var nextLastRowInd = 0;
        
        // Non-maximum suppression
        for(var i = 0; i < input.length; i++) {
            var t = undefined;
            var current = input[i];
            
            // Check above
            if(lastRow + 1 < current.y) {
                lastRow = nextLastRow;
                lastRowInd = nextLastRowInd;
            }
            
            if(nextLastRow != current.y) {
                nextLastRow = current.y;
                nextLastRowInd = i;
            }
            
            if(lastRow + 1 == current.y) {
                while(input[lastRowInd].x < current.x &&
                        input[lastRowInd].y == lastRow)
                    lastRowInd++;
                
                if(input[lastRowInd].x == current.x &&
                    lastRowInd != i) {
                        var w = lastRowInd;
                        while(nmsFlags[w] != -1)
                            w = nmsFlags[w];
                        if(input[i].score < input[w].score)
                            nmsFlags[i] = w;
                        else
                            nmsFlags[w] = i;
                    }
            }
            
            // Check left
            t = i - 1;
            if(i != 0 && input[t].y == current.y && input[t].x + 1 == current.x) {
                var currMaxAboveInd = nmsFlags[i];
                
                while(nmsFlags[t] != -1)
                    t = nmsFlags[t];
                
                if(currMaxAboveInd == -1) {
                    if(t != i) {
                        if(input[i].score < input[t].score)
                            nmsFlags[i] = t;
                        else
                            nmsFlags[t] = i;
                    }
                } else {
                    if(t != currMaxAboveInd) {
                        if(input[currMaxAboveInd].score < input[t].score) {
                            nmsFlags[currMaxAboveInd] = t;
                            nmsFlags[i] = t;                                
                        } else {
                            nmsFlags[t] = currMaxAboveInd;
                            nmsFlags[i] = currMaxAboveInd;
                        }
                    }
                }                    
            }
        }
        
        var corners = [];
        for(var i = 0; i < input.length; i++) {
            if(nmsFlags[i] == -1)
                corners.push(input[i]);
        }
        
        return corners;            
    }
}

/*
import * as CV from "CV"

export class Sharpen
{
    private id = '11bc8936-aea4-410d-92bb-0994b61de68d';
    private computeManager: CV.ComputeManagerInterface;
    private outputTexture;
    private program;
    
    constructor()
    {
        this.computeManager = CV.ComputeManager.getInstance();
        
        // Create shader
        this.computeManager.createShaderProgram(this.id, 
            ['default.vert.c'], 
            ['sharpen.frag.c'])
          .then(function(p) { this.program = p; });        
    }
    
    Process(source) {       
        return source.select(function(input) {            
            var pixelSize = [1.0 / input.width, 1.0 / input.height];
            this.computeManager.setUniformf(this.program, "pixelSize", pixelSize);            
            
            // Obtain input and output textures
            var texture = input.asTexture();
            
            if(this.outputTexture === undefined)
                this.outputTexture = this.computeManager.getOutputTexture(input.width, input.height);
            
            // Apply shader
            this.computeManager.applyShader(texture, this.program, this.outputTexture, input.width, input.height);
            
            return new CV.Image(input.width, input.height, this.outputTexture['texture']);
        });
    }
}
*/
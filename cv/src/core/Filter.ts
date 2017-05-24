/**
 * Filter.ts: Contains basic functionality that processes images using shaders.
 */
import {ComputeManager, ComputeManagerInterface} from '../core/ComputeManager'
import {ImagePool, ImagePoolInterface} from '../core/ImagePool'
import {ImageWebGLTexture} from '../core/ImageWebGLTexture'

export interface ShaderInfo
{
    id?: string;
    vertexFiles: string[];
    fragmentFiles: string[];
    
    // Variables of texture inputs
    inputNames?: string[];
}

export class Filter
{
    protected shaders: ShaderInfo[] = [];
    protected programs: WebGLProgram[] = [];
    
    protected computeManager: ComputeManagerInterface;
    protected imagePool: ImagePoolInterface;
    
    protected LINEAR: number = 0;
    
    /**
     * Sets up shaders
     */
    protected setupShaders() 
    {
        for(let i = 0; i < this.shaders.length; i++) {
            let id = this.generateProgramId(this.shaders[i]);

            this.programs[i] = null;
        
            this.computeManager.createShaderProgram(id,
                this.shaders[i].vertexFiles,
                this.shaders[i].fragmentFiles).then(function(p: WebGLProgram) {
                    this.programs[i] = p;
                    
                    if('inputNames' in this.shaders[i]) {
                        for(let j = 0; j < this.shaders[i].inputNames.length; j++) {
                            var name = this.shaders[i].inputNames[j];
                            
                            this.computeManager.associateTextureUnit(p, name, j);
                        }
                    }
                }.bind(this));
        }
    }
    
    /**
     * Returns a unique identifier for a given shader.
     * @param shader Description of the shader
     * @return Unique identifier for the shader
     */
    private generateProgramId(shader: ShaderInfo) 
    {
        if(shader.id !== undefined)
            return 'ID' + shader.id;
        
        let id = 'FL';
        for(let i = 0; i < shader.vertexFiles.length; i++)
            id += ':' + shader.vertexFiles[i];

        id += '/';
        for(let i = 0; i < shader.fragmentFiles.length; i++)
            id += ':' + shader.fragmentFiles[i];
            
        return id;
    }
    
    
    /**
     * Runs the shader designated by id on the input texture and writes the result
     * to the output texture.
     * 
     * This is a convenience method that handles the common single-input single-output case.
     * 
     * @param id Number of the shader to run
     * @param input Input texture
     * @param output Output texture
     * 
     * @return Output texture
     */
    protected runShader(id: number, input: ImageWebGLTexture, output: ImageWebGLTexture): ImageWebGLTexture
    {
        if(output === null) {
            output = this.imagePool.getWebGLTexture(input.width, input.height, true);
        }
        
        this.computeManager.activateShader(this.programs[id], output.width, output.height);
        this.computeManager.setShaderInput(0, input.getWebGLTexture());
        this.computeManager.setShaderOutput(output.getWebGLFrameBuffer());
        this.computeManager.runShader();
        
        return output;
    }
    
    
    constructor()
    {
        this.computeManager = ComputeManager.getInstance();
        this.imagePool = ImagePool.getInstance();
    }
}

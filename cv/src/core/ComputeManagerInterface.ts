export interface IComputeManagerInterface
{
    createShaderProgram(id: string, vertex: string[], fragment: string[]): Promise<WebGLProgram>;

    createTexture(width: number, height: number): WebGLTexture;

    htmlElementToWebGLTexture(element: HTMLElement, texture: WebGLTexture): void;
    imageDataToWebGLTexture(element: ImageData, texture: WebGLTexture): void;
    webGLTextureToImageData(texture: WebGLTexture, imageData: ImageData): void;

    gl(): WebGLRenderingContext;

    setUniformf(program: WebGLProgram, name: string, value: (number | number[])): void;
    setUniformi(program: WebGLProgram, name: string, value: number): void;

    applyShader(input, program: WebGLProgram, output, width: number, height: number);

    activateShader(program: WebGLProgram, width: number, height: number): void;
    setShaderInput(inputId: number, input: WebGLTexture): void;
    setShaderOutput(output: WebGLFramebuffer): void;
    runShader(): void;
}

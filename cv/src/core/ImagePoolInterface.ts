import {Image} from './Image';
import {ImageHTMLElement} from './ImageHTMLElement';
import {ImageImageData} from './ImageImageData';
import {ImageWebGLTexture} from './ImageWebGLTexture';

export interface ImagePoolInterface
{
    returnWebGLTexture(image: ImageWebGLTexture);
    returnImageData(image: ImageImageData);

    getHTMLElement(element: HTMLElement): ImageHTMLElement;
    getWebGLTexture(width: number, height: number, withFrameBuffer: boolean, caller?: string): ImageWebGLTexture;
    getImageData(width: number, height: number): ImageImageData;
}

import {ImagePoolInterface} from './ImagePoolInterface';
import {ImagePoolPrivate} from './ImagePoolPrivate';

export class ImagePool
{
    public static getInstance(): ImagePoolInterface
    {
        if (ImagePool.instance == null) {
            ImagePool.instance = new ImagePoolPrivate();
        }
        return ImagePool.instance;
    }

    private static instance: ImagePoolInterface = null;
}

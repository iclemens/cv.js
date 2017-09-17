import {ComputeManagerPrivate} from './ComputeManagerPrivate';

export class ComputeManager
{
    public static getInstance(): ComputeManagerPrivate
    {
        if (ComputeManager.instance == null) {
            ComputeManager.instance = new ComputeManagerPrivate();
        }
        return ComputeManager.instance;
    }

    private static instance = null;
}

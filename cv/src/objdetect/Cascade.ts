
export interface StageInterface
{
    thresholds: Float64Array;
    rects: Int32Array;
}

export interface CascadeInterface
{
    size: number[];
    stages: StageInterface[];
}

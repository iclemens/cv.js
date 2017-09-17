
export interface Keypoint {
    octave?: number;
    size?: number;

    x: number;
    y: number;
    xoffset?: number;
    yoffset?: number;
    score: number;
}

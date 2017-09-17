export class PerformanceMonitor
{
    private name: string;
    private windowSize: number = 100;
    private hits: number[];
    private misses: number[];
    private hitIdx: number = 0;
    private missIdx: number = 0;

    constructor(name: string)
    {
        this.name = name + ':';
        this.hits = new Array(this.windowSize);
        this.misses = new Array(this.windowSize);

        setInterval(() => {
            let current = this.hits[this.hitIdx] / 1000.0;
            let first = this.hits[(this.hitIdx + 1) % this.windowSize] / 1000.0;
            const hitRate = Math.round(this.windowSize / (current - first) * 10.0) / 10.0;

            current = this.misses[this.missIdx] / 1000.0;
            first = this.misses[(this.missIdx + 1) % this.windowSize] / 1000.0;
            const missRate = Math.round(this.windowSize / (current - first) * 10.0) / 10.0;

            // console.log('Cache Performance:',
            // this._name, hitRate, "hits/s", missRate, "misses/s");
        }, 5000);
    }

    public hit()
    {
        this.hitIdx = (this.hitIdx + 1) % this.windowSize;
        this.hits[this.hitIdx] = Date.now();
    }

    public miss()
    {
        this.missIdx = (this.missIdx + 1) % this.windowSize;
        this.misses[this.missIdx] = Date.now();
    }
}

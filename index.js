"use strict";
class Vector2 {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }
    add(that) {
        return new Vector2(this.x + that.x, this.y + that.y);
    }
    div(that) {
        return new Vector2(this.x / that.x, this.y / that.y);
    }
    mul(that) {
        return new Vector2(this.x * that.x, this.y * that.y);
    }
    sub(that) {
        return new Vector2(this.x - that.x, this.y - that.y);
    }
    //understand this.
    length() {
        return Math.sqrt(this.x * this.x + this.y * this.y);
    }
    norm() {
        const l = this.length();
        if (l == 0)
            return new Vector2(0, 0);
        return new Vector2(this.x / l, this.y / l);
    }
    array() {
        return [this.x, this.y];
    }
    scale(value) {
        return new Vector2(this.x * value, this.y * value);
    }
}
const GRID_ROWS = 10;
const GRID_COLS = 10;
const GRID_SIZE = new Vector2(GRID_COLS, GRID_ROWS);
function fillCircle(context, center, radius) {
    context.beginPath();
    context.arc(...center.array(), radius, 0, 2 * Math.PI); //PI*2 is a full circle
    context.fill();
}
function strokeLine(context, p1, p2) {
    context.beginPath();
    context.moveTo(...p1.array()); //(p1.x, p2.y); SAME as that ... spread
    context.lineTo(...p2.array()); //(p2.x, p2.y);
    context.stroke();
}
function rayStep(p1, p2) {
    return p2.sub(p1).norm().add(p2);
}
function canvasSize(context) {
    return new Vector2(context.canvas.width, context.canvas.height);
}
function renderGrid(game, context, p2) {
    context.reset();
    context.fillStyle = "#ffffff";
    context.fillRect(0, 0, context.canvas.width, context.canvas.height);
    // 600  60;
    //context.beginPath();
    const cell_w = context.canvas.width / GRID_ROWS; // 60
    const cell_h = context.canvas.height / GRID_COLS;
    context.scale(cell_w, cell_h); //60 60  - 600
    context.lineWidth = 0.02;
    //just because we scaled the canvas we don't have to calculate manually in for loop by cell_w*i
    for (let x = 0; x < GRID_ROWS; x++) {
        strokeLine(context, new Vector2(x, 0), new Vector2(x, GRID_ROWS));
    }
    for (let y = 0; y < GRID_COLS; y++) {
        strokeLine(context, new Vector2(0, y), new Vector2(GRID_COLS, y));
    }
    // console.log(game);
    //new Vector2(GRID_ROWS*0.50,GRID_COLS*0.75); // normalize..  by width/10*0.5
    context.fillStyle = "magenta";
    const p1 = new Vector2(GRID_ROWS * 0.30, GRID_COLS * 0.35); // normalize..  by width/10*0.5
    fillCircle(context, p1, 0.2);
    if (p2 !== undefined) {
        fillCircle(context, p2, 0.2);
        context.strokeStyle = "magenta";
        strokeLine(context, p1, p2);
        const p3 = rayStep(p1, p2);
        fillCircle(context, p3, 0.2);
        strokeLine(context, p2, p3);
    }
    context.fill();
}
(() => {
    const game = document.getElementById("raycast_game");
    if (game === null) {
        throw new Error("No canvas with id `game` is found");
    }
    game.width = 600;
    game.height = 600;
    const context = game.getContext("2d");
    if (context === null) {
        throw new Error("2d context is not supported");
    }
    let p2 = undefined;
    game.addEventListener("mousemove", (event) => {
        p2 = new Vector2(event.offsetX, event.offsetY).div(canvasSize(context)).mul(GRID_SIZE);
        renderGrid(game, context, p2);
    });
})();

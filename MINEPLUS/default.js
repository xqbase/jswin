/*
mineplus/default.js - JavaScript Part for Minesweeper Plus

Minesweeper Plus - a Demo for JsWin
Designed by Morning Yellow, Version: 1.11, Last Modified: Nov. 2012
Copyright (C) 2004-2012 www.xqbase.com

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
*/

/* === Begin of Constants and Macros Part === */

// Win32 Constants
var IDI_APPICON		= 1;
var IMAGE_ICON		= 1;
var LR_SHARED		= 0x8000;
var WM_SETICON		= 0x80;
var ICON_SMALL		= 0;
var ICON_LARGE		= 1;

// Layout Constants
var APP_TITLE = "Minesweeper Plus";
var CLIENT_WIDTH	= 499;
var CLIENT_HEIGHT	= 320;
var BOX_SIZE		= 16;
var DIGIT_WIDTH		= 13;
var DIGIT_HEIGHT	= 23;
var COUNTER_LEFT	= 17;
var COUNTER_TOP		= 16;
var FACE_LEFT		= 240;
var FACE_TOP		= 16;
var FACE_SIZE		= 24;
var TIMER_LEFT		= 446;
var TIMER_TOP		= 16;
var BOARD_LEFT		= 12;
var BOARD_TOP		= 55;

var FACE_TOP_PRESS	= 0;
var FACE_TOP_WIN	= -FACE_SIZE;
var FACE_TOP_LOSS	= -2 * FACE_SIZE;
var FACE_TOP_HIT	= -3 * FACE_SIZE;
var FACE_TOP_RESET	= -4 * FACE_SIZE;

var DIGIT_TOP_MINUS	= 0;
var DIGIT_TOP_BLANK	= -DIGIT_HEIGHT;
var DIGIT_TOP_ZERO	= -11 * DIGIT_HEIGHT;

var BOX_TOP_UNHIT	= 0;
var BOX_TOP_FLAG	= -BOX_SIZE;
var BOX_TOP_MARK	= -2 * BOX_SIZE;
var BOX_TOP_HITMINE	= -3 * BOX_SIZE;
var BOX_TOP_WRONG	= -4 * BOX_SIZE;
var BOX_TOP_MINE	= -5 * BOX_SIZE;
var BOX_TOP_MARKPRESS	= -6 * BOX_SIZE;
var BOX_TOP_PRESS	= -15 * BOX_SIZE;

function DIGIT_TOP(digit) {
  return DIGIT_TOP_ZERO + DIGIT_HEIGHT * digit;
}

function BOX_TOP(mines) {
  return BOX_TOP_PRESS + BOX_SIZE * mines;
}

// Game Constants
var STATUS_NONE		= 0;
var STATUS_WIN		= 1;
var STATUS_LOSS		= 2;

var BOX_MINE		= 0xF;
var BOX_HIT		= 0x10;
var BOX_FLAG		= 0x20;

var MAX_MINES		= 99;
var BOARD_ROWS		= 16;
var BOARD_COLS		= 30;
var BOARD_SIZE		= (BOARD_ROWS + 4) * (BOARD_COLS + 4);
var MAX_HIT_BOXES	= BOARD_ROWS * BOARD_COLS - MAX_MINES;
var ADJACENT_BOXES	= 8;
var NEARBY_BOXES	= 24;

var ADJACENT_DELTA = [], NEARBY_DELTA = [], IN_BOARD = [];

for (var y = -1; y <= 1; y ++) {
  for (var x = -1; x <= 1; x ++) {
    if (x != 0 || y != 0) {
      ADJACENT_DELTA.push(y * (BOARD_COLS + 4) + x);
    }
  }
}
for (var y = -2; y <= 2; y ++) {
  for (var x = -2; x <= 2; x ++) {
    if (x != 0 || y != 0) {
      NEARBY_DELTA.push(y * (BOARD_COLS + 4) + x);
    }
  }
}
for (var sq = 0; sq < BOARD_SIZE; sq ++) {
  var row = Math.floor(sq / (BOARD_COLS + 4)) - 2;
  var col = sq % (BOARD_COLS + 4) - 2;
  IN_BOARD.push(row >= 0 && row < BOARD_ROWS && col >= 0 && col < BOARD_COLS);
}

/* === End of Constants and Macros Part === */

/* === Begin of UI Part === */

var Controls = {};

function setDivTop(div, top) {
  div.style.backgroundPosition = "0px " + top + "px";
}

function setFaceTop(top) {
  setDivTop(Controls.divFace, top);
}

function setBoxTop(sq, top) {
  Controls.divBox[sq].style.backgroundPosition = "0px " + top + "px";
}

function drawDigit(arrDiv, digit) {
  if (digit > 999 || digit < -99) {
    for (var i = 0; i < 3; i ++) {
      setDivTop(arrDiv[i], DIGIT_TOP_MINUS);
    }
  } else {
    absDigit = Math.abs(digit);
    for (var i = 0; i < 3; i ++) {
      setDivTop(arrDiv[2 - i], DIGIT_TOP(absDigit % 10));
      absDigit = Math.floor(absDigit / 10);
    }
    if (digit < 0) {
      setDivTop(arrDiv[0], DIGIT_TOP_MINUS);
    }
  }
}

function appendDiv(x, y, width, height, image) {
  var div = document.createElement("div");
  div.style.left = x + "px";
  div.style.top = y + "px";
  div.style.width = width + "px";
  div.style.height = height + "px";
  div.style.backgroundImage = "url(" + image + ".gif)";
  document.body.appendChild(div);
  return div;
}

/* === End of UI Part === */

/* === Begin of Game Part === */

var Game = {};

function getMines(sq) {
  return Game.box[sq] & BOX_MINE;
}

function isHit(sq) {
  return (Game.box[sq] & BOX_HIT) != 0;
}

function isFlag(sq) {
  return (Game.box[sq] & BOX_FLAG) != 0;
}

function isUnhit(sq) {
  return (Game.box[sq] & (BOX_HIT | BOX_FLAG)) == 0;
}

function drawFace() {
  setFaceTop(Game.status == STATUS_WIN ? FACE_TOP_WIN : Game.status == STATUS_LOSS ? FACE_TOP_LOSS : FACE_TOP_RESET);
}

function drawBox(sq) {
  if (isHit(sq)) {
    var mines = getMines(sq);
    setBoxTop(sq, mines == BOX_MINE ? BOX_TOP_HITMINE : BOX_TOP(mines));
  } else if (isFlag(sq)) {
    setBoxTop(sq, BOX_TOP_FLAG);
  } else {
    setBoxTop(sq, BOX_TOP_UNHIT);
  }
}

function contains(arr, obj) {
  for (var i = 0; i < arr.length; i ++) {
    if (arr[i] == obj) {
      return true;
    }
  }
  return false;
}

function doAutoPlay() {
  var retry = true;
  while (retry) {
    retry = false;
    for (var sq = 0; sq < BOARD_SIZE; sq ++) {
      if (!(IN_BOARD[sq] && isHit(sq))) {
        continue;
      }
      var hits = 0, flags = 0, mines = getMines(sq);
      for (var i = 0; i < ADJACENT_BOXES; i ++) {
        var sq2 = sq + ADJACENT_DELTA[i];
        if (isHit(sq2)) {
          hits ++;
        } else if (isFlag(sq2)) {
          flags ++;
        }
      }
      if (hits + mines == ADJACENT_BOXES) {
        for (var i = 0; i < ADJACENT_BOXES; i ++) {
          var sq2 = sq + ADJACENT_DELTA[i];
          if (isUnhit(sq2)) {
            flagBox(sq2, false);
            retry = true;
          }
        }
      } else if (flags == mines) {
        for (var i = 0; i < ADJACENT_BOXES; i ++) {
          var sq2 = sq + ADJACENT_DELTA[i];
          if (isUnhit(sq2)) {
            hitBox(sq2, false);
            if (Game.status != STATUS_NONE) {
              return;
            }
            retry = true;
          }
        }
      }
    }
    if (retry) {
      continue;
    }
    // If no clue, start AI routine
    for (var sq = 0; sq < BOARD_SIZE; sq ++) {
      if (!(IN_BOARD[sq] && isHit(sq))) {
        continue;
      }
      var mines1 = getMines(sq);
      var unhits = [];
      for (var i = 0; i < ADJACENT_BOXES; i ++) {
        var sq2 = sq + ADJACENT_DELTA[i];
        if (isFlag(sq2)) {
          mines1 --;
        } else if (isUnhit(sq2)) {
          unhits.push(sq2);
        }
      }
      for (var i = 0; i < NEARBY_BOXES; i ++) {
        var sq2 = sq + NEARBY_DELTA[i];
        if (!(IN_BOARD[sq2] && isHit(sq2))) {
          continue;
        }
        var unhits1 = [], unhits2 = [], unhits12 = [];
        var mines2 = getMines(sq2);
        for (var j = 0; j < ADJACENT_BOXES; j ++) {
          var sq3 = sq2 + ADJACENT_DELTA[j];
          if (isHit(sq3)) {
            continue;
          }
          if (isFlag(sq3)) {
            mines2 --;
            continue;
          }
          if (contains(unhits, sq3)) {
            unhits12.push(sq3);
          } else {
            unhits2.push(sq3);
          }
        }
        if (unhits12.length == 0) {
          continue;
        }
        for (var j = 0; j < unhits.length; j ++) {
          var sq3 = unhits[j];
          if (!contains(unhits12, sq3)) {
            unhits1.push(sq3);
          }
        }
        if (mines1 - unhits1.length == mines2) {
          for (var j = 0; j < unhits1.length; j ++) {
            flagBox(unhits1[j], false);
            retry = true;
          }
          for (var j = 0; j < unhits2.length; j ++) {
            hitBox(unhits2[j], false);
            retry = true;
          }
        } else if (mines2 - unhits2.length == mines1) {
          for (var j = 0; j < unhits2.length; j ++) {
            flagBox(unhits2[j], false);
            retry = true;
          }
          for (var j = 0; j < unhits1.length; j ++) {
            hitBox(unhits1[j], false);
            retry = true;
          }
        }
        if (retry) {
          break;
        }
      }
      if (retry) {
        break;
      }
    }
  }
}

function hitBox(sqHit, autoPlay) {
  if (!isUnhit(sqHit)) {
    return;
  }

  // Lay Mines after First Hit
  if (Game.hitBoxes == 0) {
    var mines = 0;
    while (mines < MAX_MINES) {
      var row = Math.floor(Math.random() * BOARD_ROWS);
      var col = Math.floor(Math.random() * BOARD_COLS);
      var sq = (row + 2) * (BOARD_COLS + 4) + col + 2;
      if (sq != sqHit && Game.box[sq] == 0) {
        Game.box[sq] = BOX_MINE;
        mines ++;
      }
    }
    Game.timer = setInterval(function() {
      Game.seconds ++;
      drawDigit(Controls.divTimer, Game.seconds);
      if (Game.seconds == 1000) {
        clearInterval(Game.timer);
      }
    }, 1000);
  }

  if (Game.box[sqHit] == BOX_MINE) {
    // Loss
    for (var sq = 0; sq < BOARD_SIZE; sq ++) {
      if (IN_BOARD[sq]) {
        if (isFlag(sq)) {
          if (getMines(sq) != BOX_MINE) {
            setBoxTop(sq, BOX_TOP_WRONG);
          }
        } else if (getMines(sq) == BOX_MINE) {
          setBoxTop(sq, BOX_TOP_MINE);
        }
      }
    }
    Game.box[sqHit] = BOX_HIT + BOX_MINE;
    setBoxTop(sqHit, BOX_TOP_HITMINE);
    Game.status = STATUS_LOSS;
    drawFace();
    clearInterval(Game.timer);
  } else {
    // Hit
    var mines = 0;
    for (var i = 0; i < ADJACENT_BOXES; i ++) {
      if (getMines(sqHit + ADJACENT_DELTA[i]) == BOX_MINE) {
        mines ++;
      }
    }
    Game.box[sqHit] = BOX_HIT + mines;
    drawBox(sqHit);
    Game.hitBoxes ++;
    if (Game.hitBoxes == MAX_HIT_BOXES) {
      // Win
      for (var sq = 0; sq < BOARD_SIZE; sq ++) {
        if (IN_BOARD[sq] && getMines(sq) == BOX_MINE) {
          setBoxTop(sq, BOX_TOP_FLAG);
        }
      }
      Game.mines = 0;
      drawDigit(Controls.divCounter, Game.mines);
      Game.status = STATUS_WIN;
      drawFace();
      clearInterval(Game.timer);
    } else if (autoPlay) {
      doAutoPlay();
    }
  }
}

function flagBox(sq, autoPlay) {
  if (!isHit(sq)) {
    Game.box[sq] ^= BOX_FLAG;
    drawBox(sq);
    Game.mines += (isFlag(sq) ? -1 : 1);
    drawDigit(Controls.divCounter, Game.mines);
    if (autoPlay && isFlag(sq)) {
      doAutoPlay();
    }
  }
}

function restart() {
  Game.status = STATUS_NONE;
  drawFace();

  Game.mines = MAX_MINES;
  drawDigit(Controls.divCounter, Game.mines);

  Game.seconds = 0;
  drawDigit(Controls.divTimer, Game.seconds);
  if (Game.timer != null) {
    clearInterval(Game.timer);
  }

  for (var sq = 0; sq < BOARD_SIZE; sq ++) {
    if (IN_BOARD[sq]) {
      Game.box[sq] = 0;
      setBoxTop(sq, BOX_TOP_UNHIT);
    } else {
      Game.box[sq] = BOX_HIT;
    }
  }

  Game.hitBoxes = 0;
}

/* === End of Game Part === */

function main() {
  if (typeof VB == "object") {
    VB.App.Title = VB.Caption = APP_TITLE;

    // Application Icon
    var fnLoadImage = VB.GetProcAddress(JS.win32.modUser, "LoadImageA");
    var fnSendMessage = VB.GetProcAddress(JS.win32.modUser, "SendMessageA");
    var hIconSmall = JS.callProc(fnLoadImage, VB.App.hInstance, IDI_APPICON, IMAGE_ICON, 16, 16, LR_SHARED);
    var hIconLarge = JS.callProc(fnLoadImage, VB.App.hInstance, IDI_APPICON, IMAGE_ICON, 32, 32, LR_SHARED);
    JS.callProc(fnSendMessage, VB.hWnd, WM_SETICON, ICON_SMALL, hIconSmall);
    JS.callProc(fnSendMessage, VB.hWnd, WM_SETICON, ICON_LARGE, hIconLarge);

    JS.show(STYLE_FIXED, CLIENT_WIDTH, CLIENT_HEIGHT);
  }

  Controls.divCounter = [];
  for (var i = 0; i < 3; i ++) {
    Controls.divCounter.push(appendDiv(COUNTER_LEFT + DIGIT_WIDTH * i, COUNTER_TOP, DIGIT_WIDTH, DIGIT_HEIGHT, "digit"));
  }
  Controls.divFace = appendDiv(FACE_LEFT, FACE_TOP, FACE_SIZE, FACE_SIZE, "face");
  Controls.divFace.onclick = restart;
  Controls.divFace.onmousedown = function() {
    var e = arguments[0] || event;
    if (e.button != 2) {
      setFaceTop(FACE_TOP_PRESS);
    }
  };
  Controls.divFace.onmouseup = Controls.divFace.onmouseout = function() {
    drawFace();
  };
  Controls.divTimer = [];
  for (var i = 0; i < 3; i ++) {
    Controls.divTimer.push(appendDiv(TIMER_LEFT + DIGIT_WIDTH * i, TIMER_TOP, DIGIT_WIDTH, DIGIT_HEIGHT, "digit"));
  }
  Controls.divBox = new Array(BOARD_SIZE);
  for (var row = 0; row < BOARD_ROWS; row ++) {
    var y = BOARD_TOP + BOX_SIZE * row;
    var sqRow = (row + 2) * (BOARD_COLS + 4) + 2;
    for (var col = 0; col < BOARD_COLS; col ++) {
      var div = appendDiv(BOARD_LEFT + BOX_SIZE * col, y, BOX_SIZE, BOX_SIZE, "box")
      var sq = sqRow + col;
      div.onclick = (function(sq_) {
        return function() {
          if (Game.status == STATUS_NONE) {
            hitBox(sq_, true);
          }
        };
      })(sq);
      div.onmousedown = (function(sq_) {
        return function() {
          if (Game.status == STATUS_NONE) {
            var e = arguments[0] || event;
            if (e.button == 2) {
              flagBox(sq_, true);
            } else if (isUnhit(sq_)) {
              setBoxTop(sq_, BOX_TOP_PRESS);
              setFaceTop(FACE_TOP_HIT);
            }
          }
        };
      })(sq);
      div.onmouseup = div.onmouseout = (function(sq_) {
        return function() {
          if (Game.status == STATUS_NONE && isUnhit(sq_)) {
            setBoxTop(sq_, BOX_TOP_UNHIT);
            setFaceTop(FACE_TOP_RESET);
          }
        };
      })(sq);
      Controls.divBox[sq] = div;
    }
  }

  Game.box = new Array(BOARD_SIZE);
  restart();
}
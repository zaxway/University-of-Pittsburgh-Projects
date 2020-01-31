// create a global object/struct
var config = {
  blackPlayerName: "",
  blackPlayerBirthday: "",
  redPlayerName: "",
  startingPlayer: "black",
  redPlayerBirthday: "",
  blackPlayerTokens: 21,
  redPlayerTokens: 21,
  blackPlayerGames: 0,
  redPlayerGames: 0,
  countToWin: 4
};

var gameBoard = [
  [0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 0],
  [0, 0, 0, 0, 0, 0, 0]
];

var currentPlayer = config.startingPlayer;

function addDiscToBoard(color, x_pos, y_pos) {
  gameBoard[y_pos][x_pos] = color;
}


function reset_board() {
  for (var y = 0; y <= 5; y++) {
    for (var x = 0; x <= 6; x++) {
      if (gameBoard[y][x] !== 0) {
        var cell = document.querySelectorAll('.connect_four_board tr')[y].querySelectorAll('.connect_four_board td')[x];
        var currentButton = cell.children;
        currentButton[0].classList.remove(gameBoard[y][x]);
      }
    }
  }
  gameBoard = gameBoard = [
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0],
    [0, 0, 0, 0, 0, 0, 0]
  ];
  config.blackPlayerTokens = 21;
  config.redPlayerTokens = 21;
  document.getElementById("tp1").innerHTML = 'Remaining Tokens for Player 1: ' + config.blackPlayerTokens;
  document.getElementById("tp2").innerHTML = 'Remaining Tokens for Player 2: ' + config.redPlayerTokens;
}

function print_board(color) {
  for (var y = 0; y <= 5; y++) {
    for (var x = 0; x <= 6; x++) {
      if (gameBoard[y][x] !== 0) {
        var cell = document.querySelectorAll('.connect_four_board tr')[y].querySelectorAll('.connect_four_board td')[x];
        console.log(cell);
        var currentButton = cell.children;
        console.log(currentButton[0]);
        console.log("y: " + y);
        console.log("x: " + x);
        currentButton[0].classList.add(gameBoard[y][x]);
      }
    }
  }
}

function change_player() {
  if (currentPlayer === 'black') {
    currentPlayer = 'red';

    document.getElementById("turn_player").innerHTML = 'The turn player is ' + config.redPlayerName;
    document.getElementById("turn_player").style.color = "red";
    document.getElementById("turn_player").style.fontWeigth = "bold";

    document.getElementById("turn_player_birthday").innerHTML = 'Birthday of Player: ' + config.redPlayerBirthday;
    document.getElementById("turn_player_birthday").style.color = "red";
    config.blackPlayerTokens = config.blackPlayerTokens - 1;
    document.getElementById("tp1").innerHTML = 'Remaining Tokens for Player 1: ' + config.blackPlayerTokens;

  }
  else {
    currentPlayer = 'black';
    document.getElementById("turn_player").innerHTML = 'The turn player is ' + config.blackPlayerName;
    document.getElementById("turn_player").style.color = "black";
    document.getElementById("turn_player").style.fontWeigth = "bold";

    document.getElementById("turn_player_birthday").innerHTML = 'Birthday of Player: ' + config.blackPlayerBirthday;
    document.getElementById("turn_player_birthday").style.color = "black";

    config.redPlayerTokens = config.redPlayerTokens - 1;
    document.getElementById("tp2").innerHTML = 'Remaining Tokens for Player 2: ' + config.redPlayerTokens;
  }
}


function calculateAge(birthday) { // birthday is a date
   var ageDifMs = Date.now() - birthday.getTime();
   var ageDate = new Date(ageDifMs); // miliseconds from epoch
   return Math.abs(ageDate.getUTCFullYear() - 1970);
 }

function isValidDate(d) {
  return d instanceof Date && !isNaN(d);
}

function check_valid_date(bday) {
  var reg = /^(?:(?:31(\/|-|\.)(?:0?[13578]|1[02]))\1|(?:(?:29|30)(\/|-|\.)(?:0?[1,3-9]|1[0-2])\2))(?:(?:1[6-9]|[2-9]\d)?\d{2})$|^(?:29(\/|-|\.)0?2\3(?:(?:(?:1[6-9]|[2-9]\d)?(?:0[48]|[2468][048]|[13579][26])|(?:(?:16|[2468][048]|[3579][26])00))))$|^(?:0?[1-9]|1\d|2[0-8])(\/|-|\.)(?:(?:0?[1-9])|(?:1[0-2]))\4(?:(?:1[6-9]|[2-9]\d)?\d{2})$/;
  return reg.test(bday);
}

function drop_to_bottom(x_pos) {
  for (var y = 5; y > 0; y--) {
    if (gameBoard[y][x_pos] === 0) {
      return y;
    }
  }
  return 0;
}

function positionTaken(x_pos, y_pos) {
  var value = gameBoard[y_pos][x_pos];
  return value === 0 ? false : true;
}

function draw_game() {
  for (var y = 0; y <= 5; y++) {
    for (var x = 0; x <= 6; x++) {
      // check if any of the positions are not filled
      if (gameBoard[y][x] === 0) {
        return false;
      }
    }
  }
  return true;
}

function horizontalWin() {
  var currValue = null;
  var prevValue = 0;
  var tally = 0;
  // run through the gameBoard
  for (var y = 0; y <= 5; y++) {
    for (var x = 0; x <= 6; x++) {
      currValue = gameBoard[y][x];
      if (currValue == prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;
    }
    tally = 0;
    prevValue = 0;
  }
  return false;
}

function verticalWin() {
  var currValue = null;
  var prevValue = 0;
  var tally = 0;
  // run through the gameBoard
  for (var y = 0; y <= 6; y++) {
    for (var x = 0; x <= 5; x++) {
      currValue = gameBoard[x][y];
      if (currValue == prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;
    }
    tally = 0;
    prevValue = 0;
  }
  return false;
}


function diagonal_win() {
  var x = null;
  var y = null;
  var xtemp = null;
  var ytemp = null;
  var currValue = null
  var prevValue = 0;
  var tally = 0;

  for (x = 0; x <= 6; x++) {
    xtemp = x;
    ytemp = 0;

    while (xtemp <= 6 && ytemp <= 5) {
      currValue = gameBoard[ytemp][xtemp];
      if (currValue === prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;

      xtemp++;
      ytemp++;
    }
    tally = 0;
    prevValue = 0;
  }

  for (x = 0; x <= 6; x++) {
    xtemp = x;
    ytemp = 0;
    while (xtemp >= 0 && ytemp <= 5) {
      currValue = gameBoard[ytemp][xtemp];
      if (currValue === prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;

      xtemp--;
      ytemp++;
    }
    tally = 0;
    prevValue = 0;
  }

  for (y = 0; y <= 5; y++) {
    xtemp = 0;
    ytemp = y;

    while (xtemp <= 6 && ytemp <= 5) {
      currValue = gameBoard[ytemp][xtemp];
      if (currValue === prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;

      xtemp++;
      ytemp++;
    }
    tally = 0;
    prevValue = 0;
  }

  for (y = 0; y <= 5; y++) {
    xtemp = 6;
    ytemp = y;

    while (xtemp >= 0 && ytemp <= 5) {
      currValue = gameBoard[ytemp][xtemp];
      if (currValue === prevValue && currValue !== 0) {
        tally += 1;
      }
      else {
        tally = 0;
      }
      if (tally == 3) {
        return true;
      }
      prevValue = currValue;

      xtemp--;
      ytemp++;
    }
    tally = 0;
    prevValue = 0;
  }

  return false;
}

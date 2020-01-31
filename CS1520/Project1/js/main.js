config.blackPlayerName = prompt("Please enter your player name for the black coin", "Player 1");
document.getElementById("turn_player").innerHTML = 'The turn player is ' + config.blackPlayerName;

config.blackPlayerBirthday = prompt("Enter your birthday in any format", "3/02/15");
while (check_valid_date(config.blackPlayerBirthday) === false) {
  config.blackPlayerBirthday = prompt("Enter your birthday in a valid format", "3/02/15");
}
config.blackPlayerBirthday = new Date(config.blackPlayerBirthday);
var ageBlack = calculateAge(config.blackPlayerBirthday);
// if (isValidDate(config.blackPlayerBirthday))
document.getElementById("turn_player_birthday").innerHTML = 'Birthday of Player: ' + config.blackPlayerBirthday;

config.redPlayerName = prompt("Please enter your player name for the red coin", "Player 2");
config.redPlayerBirthday = prompt("Enter your birthday in any format", "2/01/13");
while (check_valid_date(config.redPlayerBirthday) === false) {
  config.redPlayerBirthday = prompt("Enter your birthday in a valid format", "3/02/15");
}
config.redPlayerBirthday = new Date(config.redPlayerBirthday);
var ageRed = calculateAge(config.redPlayerBirthday);

// if red is the older player
if (ageBlack < ageRed) {
  change_player();
}

document.getElementById("play_again").setAttribute('disabled','disabled');
document.getElementById("tp1").innerHTML = 'Remaining Tokens for Player 1: ' + config.blackPlayerTokens;
document.getElementById("tp2").innerHTML = 'Remaining Tokens for Player 2: ' + config.redPlayerTokens;

var start = new Date();

var map = new Map();
var arr = [];

  document.getElementById('1dropper').addEventListener("click", function() {
    var num = 0;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";
      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();

  });

  document.getElementById('2dropper').addEventListener("click", function() {
    var num = 1;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];

      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();
  });

  document.getElementById('3dropper').addEventListener("click", function() {
    var num = 2;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();
  });

  document.getElementById('4dropper').addEventListener("click", function() {
    var num = 3;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();
  });

  document.getElementById('5dropper').addEventListener("click", function() {
    var num = 4;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();
  });

  document.getElementById('6dropper').addEventListener("click", function() {
    var num = 5;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";


      //return;
    }
    change_player();
  });

  document.getElementById('7dropper').addEventListener("click", function() {
    var num = 6;
    var y_pos = drop_to_bottom(num);
    console.log(y_pos);
    if (positionTaken(num, y_pos)) {
      alert("Column is Full!");
      return;
    }

    addDiscToBoard(currentPlayer, num, y_pos);
    print_board(currentPlayer);

    if (horizontalWin() || verticalWin() || diagonal_win()) {
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      var elapsed = new Date() - start;
      elapsed = elapsed / 1000;
      if (currentPlayer === 'black') {
        config.blackPlayerGames = config.blackPlayerGames + 1;
        document.getElementById("p1GamesWon").innerHTML = config.blackPlayerGames + " games won";
        map.set(config.blackPlayerName, elapsed);
        alert(config.blackPlayerName + " Wins and it took time of " + elapsed + " seconds");

      }
      else {
        config.redPlayerGames = config.redPlayerGames + 1;
        document.getElementById("p2GamesWon").innerHTML = config.redPlayerGames + " games won";
        map.set(config.redPlayerName, elapsed);
        alert(config.redPlayerName + " Wins and it took time of " + elapsed + " seconds");
      }

      map[Symbol.iterator] = function* () {
        yield* [...this.entries()].sort((a, b) => a[1] - b[1]);
      }

      for (let [key, value] of map) {
        console.log(key);
        arr.push({x: key + " " + value});
      }
      alert(JSON.stringify(arr, null, 4));
      arr = [];
      //return;
    }
    else if (draw_game()) {
      alert("draw");
      document.getElementById("1dropper").setAttribute('disabled','disabled');
      document.getElementById("2dropper").setAttribute('disabled','disabled');
      document.getElementById("3dropper").setAttribute('disabled','disabled');
      document.getElementById("4dropper").setAttribute('disabled','disabled');
      document.getElementById("5dropper").setAttribute('disabled','disabled');
      document.getElementById("6dropper").setAttribute('disabled','disabled');
      document.getElementById("7dropper").setAttribute('disabled','disabled');
      document.getElementById("play_again").removeAttribute('disabled');
      document.getElementById("play_again").style.visibility = "visible";

      //return;
    }
    change_player();
  });

  document.getElementById('play_again').addEventListener("click", function() {

      reset_board();

      document.getElementById("play_again").setAttribute('disabled','disabled');
      document.getElementById("play_again").style.visibility = "hidden";

      document.getElementById("1dropper").removeAttribute('disabled');
      document.getElementById("2dropper").removeAttribute('disabled');
      document.getElementById("3dropper").removeAttribute('disabled');
      document.getElementById("4dropper").removeAttribute('disabled');
      document.getElementById("5dropper").removeAttribute('disabled');
      document.getElementById("6dropper").removeAttribute('disabled');
      document.getElementById("7dropper").removeAttribute('disabled');
      start = new Date();

  });

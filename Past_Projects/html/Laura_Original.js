/*
    Variables for player and words
*/
    var gameType = 2;
    var nick = "unknown";
    var pin = "XXXX";
    var direction = 1;
    var wordCount = 0;
    var startCoordinate = -1;
    var endCoordinate = -1;
    var start = 0;
    var word = "";
//    var idx = Math.round(1 + Math.random()*3);
    var idx = 1;
    const PlayerToColor = new Map([[0,"royalblue"],[1,"blue"],[2,"red"],[3,"yellow"],[4,"green"],[5,"brown"]]);
    const NumberToGameType = new Map([[0,"unknown"],[1,"Game1"],[2,"Game2"],[3,"Game3"],[4,"Game4"]]);
    const DirToWordType = new Map([[1,"horizontal"],[2,"bHorizontal"],[3,"vertical"],[4,"bVertical"],
                                   [5,"bottomLeftTopRight"],[6,"topRightBottomLeft"],[7,"bottomRightTopLeft"],[8,"topLeftBottomRight"]]);
/*
    Create a one-dimensional array of 2500 elements for the grid 50 by 50.
    Random fill the array with 2500 characters     
*/
    const squareGrid = new Array(2500);
    for (let index=0;index<squareGrid.length;index++) {
        let charCode = Math.round(97 + Math.random() * 25);
        squareGrid[index]=String.fromCharCode(charCode);
//        squareGrid[index] = '?';
        const button = document.createElement("button");
        button.setAttribute("id",index);
        button.setAttribute("onclick","change_color("+index+");");
        button.innerHTML = squareGrid[index];
        if(index % 50 == 0) {
           linebreak = document.createElement("br");
           board.appendChild(linebreak);
        }
        board.appendChild(button);
     }
/*
   add a list of words to the grid.
*/
      addWordToGrid("arlington",1,110);
      addWordToGrid("texas",2,975);
      addWordToGrid("spirituality",5,1000);
      addWordToGrid("mississippi",3,422);
      addWordToGrid("abilities",4,849);
      addWordToGrid("accessibility",1,462);
      addWordToGrid("accounts",7,562);
      addWordToGrid("ultimate",6,340);
      addWordToGrid("according",8,462);
// Display how many words in Word Bank
      document.getElementById("p5h4_7").innerHTML="Words Left: "+wordCount
/*
   Function to add a word to the table Word Bank
*/
      function addWordBank(tableID,item1) {
        var table = document.getElementById(tableID);
        var row = table.insertRow(table.rows.length);
        var cell1 = row.insertCell(0);
        cell1.innerHTML = item1;
      }
/*
   When button Send Message is clicked, this function is executed. 
*/
      function postMessage() {}
/*
 
*/
/*
   Function to find the direction of a word based on the start coordinate and end coordinate.
   There are eight directions: 1=horizontal;2=left-horizontal;3=vertical;4=down vertical;5=northeast diagonal;
   6=southwest diagonal;7=northwest diagonal;8=southeast diagonal;
*/
    function getDirection(v1, v2) {
       let x = v1 % 50;
       let y = Math.floor(v1 / 50);
       let x2 = v2 % 50;
       let y2 = Math.floor(v2 / 50);
       if((v1<0) || (v2<0)) return -2;
       if(y==y2)
       {
         if(x2-x>0)
           return 1;
         else
           return 2;
       }
       else if (x==x2)
       {
         if(y-y2>0)
           return 3;
         else
           return 4;
       } 
       else if(Math.abs(x2-x) == Math.abs(y2-y))
       {
         if((x2-x)>0 && (y-y2)>0)
           return 5;
         else if((x2-x)<0 && (y-y2)>0)
           return 6;
         else if((x2-x)>0 && (y-y2)<0)
           return 7;
         else if((x2-x)<0 && (y-y2)<0)
           return 8;
       }
       else
         return -1;
    }
/*
   When the button Game Room is clicked, this function is ran. It will display the page 5 and hide page 4.
*/
    function GameRoom()
    {
      document.getElementById("page4").style.display="none"; 
      document.getElementById("page5").style.display="block";
      document.getElementById("p5p").innerHTML="You are: "+nick;
    }
/*
   When the button Winner is clicked, this function is ran. It will display the page 6 and hide page 5.
*/
    function Winner()
    {
      document.getElementById("page5").style.display="none"; 
      document.getElementById("page6").style.display="block";
    }
/*
   When the button Loser is clicked, this function is ran. It will display the page 7 and hide page 5.
*/
    function Loser()
    {
      document.getElementById("page5").style.display="none"; 
      document.getElementById("page7").style.display="block";
    }
/*
   This function will display the page 1 and hide page 2 and 3.

    function ReturnPage1()
    {
      document.getElementById("page2").style.display="none"; 
      document.getElementById("page3").style.display="none"; 
      document.getElementById("page1").style.display="block";        
    }
*/
/*
   When the button New Player is clicked, this function is ran. It will display the page 2 and hide page 1 and 3.
*/
    function NewPlayer()
    {
      document.getElementById("page1").style.display="none"; 
      document.getElementById("page3").style.display="none"; 
      document.getElementById("page2").style.display="block";        
    }
/*
   When the button Return Player is clicked, this function is ran. It will display the page 3 and hide page 1 and 2.
*/
    function ReturnPlayer()
    {
      document.getElementById("page1").style.display="none"; 
      document.getElementById("page2").style.display="none"; 
      document.getElementById("page3").style.display="block";        
    }
/*
   This function will set the game type (2-player,3-player,4-player) and change the background color of the selected button  .
*/
    function SelectPlayer(id)
    {
      if(id=="p2bt3") {
        gameType = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt4").className="button button4"; 
        document.getElementById("p2bt5").className="button button4";
      }        
      else if(id=="p2bt4") {
        gameType = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt3").className="button button4"; 
        document.getElementById("p2bt5").className="button button4";
      }        
      else if(id=="p2bt5") {
        gameType = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt4").className="button button4"; 
        document.getElementById("p2bt3").className="button button4";
      }        
      else if(id=="p3bt3") {
        gameType = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt4").className="button button4"; 
        document.getElementById("p3bt5").className="button button4";
      }        
      else if(id=="p3bt4") {
        gameType = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt3").className="button button4"; 
        document.getElementById("p3bt5").className="button button4";
      }        
      else if(id=="p3bt5") {
        gameType = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt4").className="button button4"; 
        document.getElementById("p3bt3").className="button button4";
      }  
      else if(id=="p6bt3") {
        gameType = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt4").className="button button4"; 
        document.getElementById("p6bt5").className="button button4";
      }        
      else if(id=="p6bt4") {
        gameType = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt3").className="button button4"; 
        document.getElementById("p6bt5").className="button button4";
      }        
      else if(id=="p6bt5") {
        gameType = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt4").className="button button4"; 
        document.getElementById("p6bt3").className="button button4";
      }  
      else if(id=="p7bt3") {
        gameType = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt4").className="button button4"; 
        document.getElementById("p7bt5").className="button button4";
      }        
      else if(id=="p7bt4") {
        gameType = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt3").className="button button4"; 
        document.getElementById("p7bt5").className="button button4";
      }        
      else if(id=="p7bt5") {
        gameType = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt4").className="button button4"; 
        document.getElementById("p7bt3").className="button button4";
      }  
    }
 /*
   When the button Find Game is clicked, this function is executed. This function ensure that name and pin are filled; otherwise, 
   it will display the page Game Lobby and add the player name to the table Players Waiting and send the player info to the app server.  
*/
   function FindGame(i)
    { 
      nick=document.getElementById("name").value;
      pin=document.getElementById("pin").value;
      if(nick != "" && pin != "") {
      document.getElementById("p4h4").innerHTML="You are: "+nick;
      document.getElementById("p4h4_2").innerHTML="Game Type: "+gameType+"-Player";
      document.getElementById("page2").style.display="none"; 
      document.getElementById("page3").style.display="none"; 
      document.getElementById("page4").style.display="block";
      document.getElementById("page6").style.display="none";
      document.getElementById("page7").style.display="none";
      if(i==1) 
        addRow("p4table",nick,gameType+"-Player")
      else {
        deleteRow("p4table")
        addRow("p4table",nick,gameType+"-Player");
       }
      }
      else {
        document.getElementById("p2errMsg2").innerHTML="Please enter your name and create a new pin.";
      }       
      sendUpdate();
    }
 /*
   Same as FindGame,but from page Return Player (page 3)
   When the button Find Game is clicked, this function is executed. This function ensure that name and pin are filled; otherwise, 
   it will display the page Game Lobby and add the player name to the table Players Waiting and send the player info to the app server.  
*/
    function FindGame2(i)
    { 
      nick=document.getElementById("name2").value;
      pin=document.getElementById("pin2").value;
      if(nick != "" && pin != "") {
      document.getElementById("p4h4").innerHTML="You are: "+nick;
      document.getElementById("p4h4_2").innerHTML="Game Type: "+gameType+"-Player";
      document.getElementById("page2").style.display="none"; 
      document.getElementById("page3").style.display="none"; 
      document.getElementById("page4").style.display="block";
      if(i==1) 
        addRow("p4table",nick,gameType+"-Player")
      else {
        deleteRow("p4table")
        addRow("p4table",nick,gameType+"-Player");
        }
      }
      else {
        document.getElementById("p3errMsg2").innerHTML="Please enter your name and pin number";
      }       
      sendUpdate();

      // Set webpage title to the player name for testing, remove later
      
    }
/*
    When any button in the grid is clicked, this function is executed. The background color is changed to the color associated with 
    the player,the color of the word will be changed if the start and the end coordinates are found. Also, send the found word back to the 
    App server.    
*/
    function change_color(id) {
       let x = id % 50;
       let y = Math.floor(id / 50);   
       const letter = document.getElementById(id).innerHTML;
       let bcolor = document.getElementById(id).style.backgroundColor;
       document.getElementById(id).style.backgroundColor = PlayerToColor.get(idx);
      if(start==0) {
         startCoordinate = id;
         start = 1;
      }
      else {
        endCoordinate = id;
        start = 0;
      }         
      if(startCoordinate >= 0 && endCoordinate >= 0) {
	highlightWord();
        sendUpdate();
        startCoordinate=endCoordinate=-1;
        start=0;
      }
    }
/*
   This function will highlight the word based on the start and end coordinated. It will get the direction of the word and hightlight all
   the characters of the word according to the direction.
*/
    function highlightWord() {
       direction = getDirection(startCoordinate,endCoordinate);
       if(direction==1) {
         for(let i=startCoordinate;i<=endCoordinate;i++) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
         }
       }    
       else if(direction==2) {      
         for(let i=startCoordinate;i>=endCoordinate;i--) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==3) {    
         for(let i=startCoordinate;i>=endCoordinate;i -=50) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==4) {     
         for(let i=startCoordinate;i<=endCoordinate;i +=50) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==5) {     
         for(let i=startCoordinate;i>=endCoordinate;i -=49) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==6) {     
         for(let i=startCoordinate;i>=endCoordinate;i -=51) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==7) {     
         for(let i=startCoordinate;i<=endCoordinate;i +=51) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       else if(direction==8) {     
         for(let i=startCoordinate;i<=endCoordinate;i +=49) {
           document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx);
           word += document.getElementById(i).innerHTML;
           }
       }
       StrikethroughWord(word);
       word="";
    }
    function StrikethroughWord(word) {
        var table = document.getElementById("p5table4");
        for(let i = 0; i < table.rows.length;i++) {
          let cell0 = table.rows[i].cells[0];
          if (cell0.innerHTML == word) cell0.innerHTML = "<del>"+word+"</del>";
        }
    
    }
/*
   When the button Reset Board is clicked, this function is executed. It will reset the background color of all the selected buttons. 
*/
    function ResetBoard() {
      start = 0;
      startCoordinate=endCoordinate=-1;
      for (let i=0;i<squareGrid.length;i++)
        document.getElementById(i).style.backgroundColor = "PaleTurquoise";
    }
/*
    This function add a word to the grid. The word can be added using any direction and start array element
*/
    function addWordToGrid(Word,dir,startPosition) {
       let A = Array.from(Word);
       let l = A.length;
       addWordBank("p5table4",Word);
       wordCount++;
       if(dir==1)
         for(let i=startPosition;i<startPosition+l;i++)
           document.getElementById(i).innerHTML=A[i-startPosition];
       else if(dir==2)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition-i).innerHTML=A[i];
       else if(dir==3)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition+i*50).innerHTML=A[i];
       else if(dir==4)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition-i*50).innerHTML=A[i];
       else if(dir==5)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition-i*(50-1)).innerHTML=A[i];
       else if(dir==6)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition+i*(50-1)).innerHTML=A[i];
       else if(dir==7)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition-i*(50+1)).innerHTML=A[i];
        else if(dir==8)
         for(let i=0;i<l;i++)
           document.getElementById(startPosition+i*(50+1)).innerHTML=A[i];
    }
/*
   This function adds a row at the bottom of table Player Waiting or Games Won Leaderboard or Points LeaderBoard
*/
    function addRow(tableID,item1,item2) {
      var table = document.getElementById(tableID);
      var row = table.insertRow(table.rows.length);  
      var cell1 = row.insertCell(0);
      var cell2 = row.insertCell(1);
      cell1.innerHTML = item1;
      cell2.innerHTML = item2;
    }
/*
   This function removes the last row of table Player Waiting or Games Won Leaderboard or Points LeaderBoard
*/
    function deleteRow(tableID) {
      var table = document.getElementById(tableID);
      table.deleteRow(table.rows.length-1);
    }

/*
   This code is for the clock timer . Get it from W3schools.com
*/
var countDownDate = new Date("May 1, 2024 22:00:00").getTime();
// Update the count down every 1 second
    var x = setInterval(function() {
    var now = new Date().getTime();
    var distance = countDownDate - now;
    var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    var seconds = Math.floor((distance % (1000 * 60)) / 1000);
    document.getElementById("p5h1").innerHTML = minutes + ":" + seconds;
    if (distance < 0) {
      clearInterval(x);
      document.getElementById("p5h1").innerHTML = "GAME OVER";
    }
}, 1000);
/*
    This section setup websocket connection and receives data objects from the app server using json.
    Based on the TicTacToe codes. 
*/
    class UserEvent {
        PlayerNick = "unknown";
        Pin = "xxxx";
        gameType = 0;
        Button = -1;
        PlayerIdx = -1;
        GameId = 0;
        StartCoordinate = -1;
        EndCoordinate = -1;
        wordType = 1;
    }
    var connection = null;
//    var serverUrl;
    var gameid = -1;
//    serverUrl = "ws://" + window.location.hostname +":"+ (parseInt(location.port) + 100);
    let serverUrl = "ws://" + window.location.hostname + `:${parseInt(window.location.port) + 100}`;
    // Create the connection with the server
    connection = new WebSocket(serverUrl);
    connection.onopen = function (evt) {
        console.log("open");
    }
    connection.onclose = function (evt) {
        console.log("close");
        document.getElementById("topMessage").innerHTML = "Server Offline"
    }
    connection.onmessage = function (evt) {
        var msg;
        msg = evt.data;

        console.log("Message received: " + msg);
        const obj = JSON.parse(msg);

        if ('YouAre' in obj) {
            if (obj.YouAre == "Player0") {
                idx = 0;
            }
            else if(obj.YouAre == "Player1"){
                idx = 1;
            }
            else if(obj.YouAre == "Player2"){
                idx = 2;
            }
            else if(obj.YouAre == "Player3"){
                idx = 3;
            }
            else if(obj.YouAre == "Player4"){
                idx = 4;
            }
            gameid = obj.GameId;
        }
        else if ('CurrentTurn' in obj) {
            // show statistics to everyone
            var t = obj.Stats;
            if (t) {
/*
//                document.getElementById("timeMsg").innerHTML = "elapsed time " + t.RunningTime;
//                document.getElementById("statMsg").innerHTML =
                    " in progress " + t.GamesInProgress + " XWin " + t.XWins + " OWin " + t.OWins +
                    " Draw " + t.Draws + " Total " + t.TotalGames;
                  document.getElementById("p4h4_3").innerHTML = "Active Games : "+t.GamesInProgress;
*/
            }

            // only pay attention to this game
            if (gameid == obj.GameId) {
/*
                // button state to display values
                document.getElementById("b1").value = ButtonStateToDisplay.get(obj.Button[0]);
                document.getElementById("b2").value = ButtonStateToDisplay.get(obj.Button[1]);
                document.getElementById("b3").value = ButtonStateToDisplay.get(obj.Button[2]);
                document.getElementById("b4").value = ButtonStateToDisplay.get(obj.Button[3]);
                document.getElementById("b5").value = ButtonStateToDisplay.get(obj.Button[4]);
                document.getElementById("b6").value = ButtonStateToDisplay.get(obj.Button[5]);
                document.getElementById("b7").value = ButtonStateToDisplay.get(obj.Button[6]);
                document.getElementById("b8").value = ButtonStateToDisplay.get(obj.Button[7]);
                document.getElementById("b9").value = ButtonStateToDisplay.get(obj.Button[8]);
                // the message line
                document.getElementById("topMessage").innerHTML = obj.Msg[idx];
*/
            }
        }
    }
/*
    Send info about player info and game status (UserEvent class) using json to the app server
*/
    function sendUpdate() {
        U = new UserEvent();
        U.Button = -1;
        if(idx == 0)
            U.PlayerIdx = "Player0";
        else if(idx == 1)
            U.PlayerIdx = "Player1";
        else if(idx == 2)
            U.PlayerIdx = "Player2";
        else if(idx == 3)
            U.PlayerIdx = "Player3";
        else if(idx == 4)
            U.PlayerIdx = "Player4";
        U.GameId = gameid;
        U.PlayerNick = nick;
        U.gameType = NumberToGameType.get(gameType);
        U.Pin = pin;
        U.StartCoordinate = startCoordinate;
        U.EndCoordinate = endCoordinate;
        U.wordType = DirToWordType.get(direction);
        console.log(U);
        if (connection.readyState === WebSocket.OPEN) {
          connection.send(JSON.stringify(U));
          console.log(JSON.stringify(U))
        }
        else {
          console.log("Connection not open. Unable to send update.");
        }
    }
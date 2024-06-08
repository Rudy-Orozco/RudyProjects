var Button_ = -1;
var PlayerNick_ = "";
var Pin_ = -1;
var Invoke_ = -1;
var Status_ = -1;
var Type_ = 2;
var State_ = -1;
var idx_ = 1;
var playID = -1;
var start = 0;
var startx = 0;
var word = "";
var wordCount = 0;
var GameId = -1;
var button;
//var gameNew_ = 0;

var ptendgame = "";

var startCoordinate = -1;
var endCoordinate = -1;

var foreignStartCoordinate = -1;
var foreignEndCoordinate = -1;

var direction = -1;

var gameNew_ = 1;

const squareGrid = new Array(2500);

const PlayerToColor = new Map([[0,"royalblue"],[1,"blue"],[2,"red"],[3,"yellow"],[4,"green"],[5,"brown"]]);
const NumberToGameType = new Map([[0,"unknown"],[1,"Game1"],[2,"Game2"],[3,"Game3"],[4,"Game4"]]);
const DirToWordType = new Map([[1,"horizontal"],[2,"bHorizontal"],[3,"vertical"],[4,"bVertical"],
                                   [5,"bottomLeftTopRight"],[6,"topRightBottomLeft"],[7,"bottomRightTopLeft"],[8,"topLeftBottomRight"]]);

class ServerEvent {
    State = -1
}

class UserEvent {
    Invoke = 0;
    Button = -1;
    State = -1;

    PlayerNick = "";
    Pin = -1;
    Status = -1;
    Type = -1  
    GameId = -1;
    
    idx = -1;
    playID = -1;
    start = 0;
    word = "";
}

var connection = null;

serverUrl = "ws://" + window.location.hostname +":9106";
//9880 for locoal
//9106 for website
// Create the connection with the server
connection = new WebSocket(serverUrl);

connection.onopen = function (evt) {
    console.log("open");
}

connection.onclose = function (evt) {
    console.log("close");
    document.getElementById("topMessage").innerHTML = "Server Offline";
}

connection.onmessage = function (evt) {
    var msg;
    msg = evt.data;
    
    console.log("Message received: " + msg);
    const obj = JSON.parse(msg);

    if (obj.type == 'chat' && obj.GameId == GameId) {
      console.log("Messenger: " + obj.PlayerNick);    
      displayChatMessage(obj.text);
     
    } else {
      console.log("obj.state: " + obj.state);
      console.log("obj.GameId: " + obj.GameId);
      console.log("Client GameId: " + GameId);
      console.log("obj.pt: " + obj.pt);
      Invoke_ = -1;
    }
    
    if (obj.state == 1 && obj.gameNew == 1) {   // Setup Game and Start

      {
        Status_ = 0;

        obj.player.forEach(playObj => {
          if(PlayerNick_ == playObj.PlayerNick)
          {
            if(playObj.pt == "Player1")
            {
              idx = 1;
            }
            else if(playObj.pt == "Player2")
            {
              idx = 2;
            }
            else if(playObj.pt == "Player3")
            {
              idx = 3;
            }
            else if(playObj.pt == "Player4")
            {
              idx = 4;
            }
          }
        })

        gameNew_ = 0;

        var count = 0;
        for (let i = 0; i < 50; i++)
        {
          for (let j = 0; j < 50; j++)
          {
            squareGrid[count] = obj.g.grid[i][j];

            const button = document.createElement("button");

            button.setAttribute("id",count);
            button.setAttribute("onclick","change_color("+count+");");

            button.innerHTML = squareGrid[count];

            board.appendChild(button);
            count++;
          }
          linebreak = document.createElement("br");
          board.appendChild(linebreak);
        }

        obj.g.placedWords.forEach(wordObj => {
            addWordBank("p5table4",wordObj.word);
            wordCount++;
          })

          obj.player.forEach(playObj => {
              if(playObj.pt == "Player1")
              {
                document.getElementById("p5pone").innerHTML=""+playObj.PlayerNick;
              }
              else if(playObj.pt == "Player2")
              {
                document.getElementById("p5ptwo").innerHTML=""+playObj.PlayerNick;
              }
              else if(playObj.pt == "Player3")
              {
                document.getElementById("p5pthre").innerHTML=""+playObj.PlayerNick;
              }
              else if(playObj.pt == "Player4")
              {
                document.getElementById("p5pfour").innerHTML=""+playObj.PlayerNick;
              }
          })
    

        State = 0;

        if(GameId == -1)
        {
          GameId = obj.GameId;
        }
        
        GameRoom();
        startTimer();
        sendUpdate();
      }
    }
    if (obj.state == 2 && obj.GameId == GameId) // Update the current website and 
    {
      foreignstartCoordinate = obj.startCoordinate;
      foreignendCoordinate = obj.endCoordinate;

      console.log("Tried to change color " + msg);
      State = 0;
      
      
      if(obj.wordchosen == 1)
      {
        var x = document.getElementById("myAudio"); 
        x.play();

        if(obj.idx == 1)
        {
          let intElement = document.getElementById("p5poneP");
          intElement.textContent = obj.points;
        }
        else if(obj.idx == 2)
        {
          let intElement = document.getElementById("p5ptwoP");
          intElement.textContent = obj.points;
        }
        else if(obj.idx == 3)
        {
          let intElement = document.getElementById("p5pthreP");
          intElement.textContent = obj.points;
        }
        else if(obj.idx == 4)
        {
          let intElement = document.getElementById("p5pfourP");
          intElement.textContent = obj.points;
        }
      }

      change_color2(obj.Button, obj.idx);
      sendUpdate();
    }
    if (obj.state == 3 && obj.GameId == GameId)
    {
      console.log("Game Ended " + msg);

      var mostPoints = 0;
      var winner = "";

      obj.LeadB.PointsEarnedPlace.forEach(playObj => {
        if(playObj.Points > mostPoints)
        {
          mostPoints = playObj.Points;
          winner = playObj.PlayerNick;
        }
      });

      if(PlayerNick_ == winner)
      {
        Winner();
      }
      else
      {
        Loser();
      }

      var count = 0;
      for (let i = 0; i < 50; i++)
      {
        for (let j = 0; j < 50; j++)
        {
          const button = document.getElementById(count);
          button.remove();
          count++;
        }
      }

      const board = document.getElementById('board');
      const linebreaks = board.querySelectorAll('br');
      linebreaks.forEach(linebreak => {board.removeChild(linebreak);});

      document.getElementById("p5pone").innerHTML="";
      document.getElementById("p5pone").innerHTML="";
      document.getElementById("p5pone").innerHTML="";
      document.getElementById("p5pone").innerHTML="";
      let intDel = document.getElementById("p5poneP");
      intDel.textContent = 0;
      intDel = document.getElementById("p5ptwoP");
      intDel.textContent = 0;
      intDel = document.getElementById("p5pthreP");
      intDel.textContent = 0;
      intDel = document.getElementById("p5pfourP");
      intDel.textContent = 0;
    }    
}

function NewPlayer(){
    document.getElementById("page1").style.display="none"; 
    document.getElementById("page3").style.display="none"; 
    document.getElementById("page2").style.display="block";        
}

function ReturnPlayer()
{
    document.getElementById("page1").style.display="none"; 
    document.getElementById("page2").style.display="none"; 
    document.getElementById("page3").style.display="block";        
}

function GameRoom()
{
    document.getElementById("page4").style.display="none"; 
    document.getElementById("page5").style.display="block";
    document.getElementById("p5p").innerHTML="You are: "+PlayerNick_;
}

function FindGame() {   // Button Function
    U = new UserEvent();

    PlayerNick_=document.getElementById("name").value;
    Pin_=document.getElementById("pin").value;
    
    U.Invoke= 1;

    U.PlayerNick = PlayerNick_;
    U.Pin = Pin_;
    U.Type = Type_;

    GameId = -1;
    Status_ = 1;

    connection.send(JSON.stringify(U));
    console.log(JSON.stringify(U));

    document.getElementById("page2").style.display="none"; 
    document.getElementById("page3").style.display="none"; 
    document.getElementById("page4").style.display="block";
    document.getElementById("page6").style.display="none";
    document.getElementById("page7").style.display="none";
}

function StartGame() {
    // SETUP THE WORD GRID

    var coujnt = 0;
    for (let i = 0; i < 50; i++)
    {
        for (let j = 0; j < 50; j++)
        {
            squareGrid[count] = grid[i][j];

            const button = document.createElement("button");

            button.setAttribute("id",index);
            button.setAttribute("onclick","change_color("+index+");");

            button.innerHTML = squareGrid[index];

            if(index % 50 == 0) {
                linebreak = document.createElement("br");
                board.appendChild(linebreak);
            }

            board.appendChild(button);
            count++;
        }
    }

    /*
    for (let i = 0; i < sizeofwordarray; i++)
    {
        addWordBank("p5table4",wordarry[i]);
    }
    */
    //some how start timer

    //set up leaderboard
    
}

function SelectPlayer(id)
    {
      if(id=="p2bt3") {
        Type_ = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt4").className="button button4"; 
        document.getElementById("p2bt5").className="button button4";
      }        
      else if(id=="p2bt4") {
        Type_ = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt3").className="button button4"; 
        document.getElementById("p2bt5").className="button button4";
      }        
      else if(id=="p2bt5") {
        Type_ = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p2bt4").className="button button4"; 
        document.getElementById("p2bt3").className="button button4";
      }        
      else if(id=="p3bt3") {
        Type_ = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt4").className="button button4"; 
        document.getElementById("p3bt5").className="button button4";
      }        
      else if(id=="p3bt4") {
        Type_ = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt3").className="button button4"; 
        document.getElementById("p3bt5").className="button button4";
      }        
      else if(id=="p3bt5") {
        Type_ = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p3bt4").className="button button4"; 
        document.getElementById("p3bt3").className="button button4";
      }  
      else if(id=="p6bt3") {
        Type_ = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt4").className="button button4"; 
        document.getElementById("p6bt5").className="button button4";
      }        
      else if(id=="p6bt4") {
        Type_ = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt3").className="button button4"; 
        document.getElementById("p6bt5").className="button button4";
      }        
      else if(id=="p6bt5") {
        Type_ = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p6bt4").className="button button4"; 
        document.getElementById("p6bt3").className="button button4";
      }  
      else if(id=="p7bt3") {
        Type_ = 2;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt4").className="button button4"; 
        document.getElementById("p7bt5").className="button button4";
      }        
      else if(id=="p7bt4") {
        Type_ = 3;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt3").className="button button4"; 
        document.getElementById("p7bt5").className="button button4";
      }        
      else if(id=="p7bt5") {
        Type_ = 4;
        document.getElementById(id).className="button"; 
        document.getElementById("p7bt4").className="button button4"; 
        document.getElementById("p7bt3").className="button button4";
      }  
    }

    function change_color(id) {
        let x = id % 50;
        let y = Math.floor(id / 50);   
        //const letter = document.getElementById(id).innerHTML;
        //let bcolor = document.getElementById(id).style.backgroundColor;
        document.getElementById(id).style.backgroundColor = PlayerToColor.get(idx);
        Button_ = id;
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
        Invoke_ = 2;
         sendUpdate();
         startCoordinate=endCoordinate=-1;
         start=0;
       }
     }

     function change_color2(id, idx2) {
      let x = id % 50;
      let y = Math.floor(id / 50);   
      //const letter = document.getElementById(id).innerHTML;
      //let bcolor = document.getElementById(id).style.backgroundColor;
      let b = document.getElementById(id);
      b.style.backgroundColor = PlayerToColor.get(idx2);

      Button_ = id;
     if(startx==0) {
        foreignstartCoordinate = id;
        startx = 1;
     }
     else {
       foreignendCoordinate = id;
       startx = 0;
     }         
     if(foreignstartCoordinate >= 0 && foreignendCoordinate >= 0) {
        highlightWord2(idx2);
       foreignstartCoordinate=foreignendCoordinate=-1;
       startx=0;
     }
   }

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

     function highlightWord2(idx2) {
      direction = getDirection(foreignstartCoordinate,foreignendCoordinate);
      if(direction==1) {
        for(let i=foreignstartCoordinate;i<=foreignendCoordinate;i++) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
        }
      }    
      else if(direction==2) {      
        for(let i=foreignstartCoordinate;i>=foreignendCoordinate;i--) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==3) {    
        for(let i=foreignstartCoordinate;i>=foreignendCoordinate;i -=50) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==4) {     
        for(let i=foreignstartCoordinate;i<=foreignendCoordinate;i +=50) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==5) {     
        for(let i=foreignstartCoordinate;i>=foreignendCoordinate;i -=49) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==6) {     
        for(let i=foreignstartCoordinate;i>=foreignendCoordinate;i -=51) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==7) {     
        for(let i=foreignstartCoordinate;i<=foreignendCoordinate;i +=51) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      else if(direction==8) {     
        for(let i=foreignstartCoordinate;i<=foreignendCoordinate;i +=49) {
          document.getElementById(i).style.backgroundColor = PlayerToColor.get(idx2);
          word += document.getElementById(i).innerHTML;
          }
      }
      StrikethroughWord(word);
      word="";
   }

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

     function addWordBank(tableID, item1) {
      var table = document.getElementById(tableID).getElementsByTagName('tbody')[0];
      var lastRow = table.lastElementChild;
      var cellCount = lastRow ? lastRow.cells.length : 0;
  
      // Check if the last row is full
      if (!lastRow || cellCount === 2) {
          lastRow = table.insertRow(-1); // Create a new row
      }
      
      var cell = lastRow.insertCell(-1);
      cell.innerHTML = item1; // Add the word to the cell
    }
  

    function ResetBoard() {
      start = 0;
      startCoordinate=endCoordinate=-1;
      for (let i=0;i<squareGrid.length;i++)
        document.getElementById(i).style.backgroundColor = "PaleTurquoise";
    }

     function sendUpdate() {
        U = new UserEvent();
        U.Button = Button_;
        U.Invoke = Invoke_;
        U.GameId = GameId;
        U.State = State;
        U.PlayerNick = PlayerNick_;
        U.Pin = Pin_;
        U.StartCoordinate = endCoordinate;
        U.EndCoordinate = startCoordinate;
        U.gameNew = gameNew_;
        U.idx = idx;
        U.Status = Status_;
        /*
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
        
        
        U.gameType = NumberToGameType.get(gameType);
        
        U.StartCoordinate = startCoordinate;
        U.EndCoordinate = endCoordinate;
        U.wordType = DirToWordType.get(direction);
        */
        console.log(U);
        if (connection.readyState === WebSocket.OPEN) {
          connection.send(JSON.stringify(U));
          console.log(JSON.stringify(U))
        }
        else {
          console.log("Connection not open. Unable to send update.");
        }
    }
  
    function displayChatMessage(message) {
      const messagesContainer = document.getElementById('mb-messages');
      if (messagesContainer) {
          const messageElement = document.createElement('div');
          messageElement.textContent = message;
          messagesContainer.appendChild(messageElement);
          messagesContainer.scrollTop = messagesContainer.scrollHeight; // Scroll to the bottom
      } else {
          console.error('Failed to find the messages container.');
      }
    }
    
    function sendChatMessage() {
      const chatInput = document.getElementById('mb-messageInput');
      const message = chatInput.value.trim();
      if (message) {
          const chatMessage = { type: 'chat', text: message, playerNick: PlayerNick_, GameId: GameId};
          if (connection.readyState === WebSocket.OPEN) {
              connection.send(JSON.stringify(chatMessage));
              chatInput.value = '';  // Clear the chat input after sending
          } else {
              console.error("WebSocket is not open. Try again later.");
              alert("Cannot send message. Connection is closed.");
          }
      }
    }

    function startTimer() {
      var countDownDate = new Date().getTime() + 5 * 60 * 1000; 
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

          Invoke_ = 3;

          sendUpdate();
        }
      }, 1000);
    }
  

    /*
    
    Coord1: [0,32]
    Coord2: [12,44]
    Button = 593
    
    min = 0, max = 49
    
    [Y+1,X+1]
    
    startCoordinate = 593
    endCoordinate = 32
    
    [idx/50, idx % 50]
    
    startCoord = [11,43]
    endCoord = [0,32]
    
    startCoordinate = 67
    endCoordinate = 51
    startCoord = [1,17+1]
    endCoord = [1,1]
    */

    function Winner()
    {
      document.getElementById("page5").style.display="none"; 
      document.getElementById("page6").style.display="block";
    }

        function Loser()
    {
      document.getElementById("page5").style.display="none"; 
      document.getElementById("page7").style.display="block";
    }
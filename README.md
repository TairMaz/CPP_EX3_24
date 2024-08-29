# CPP_EX3_24

## Class Hierarchy Overview:
Catan: Manages the overall game, players, turns, and main game logic.

Player: Represents a player in the game, including their resources and development cards.

Board: Represents the game board, including tiles, paths, and nodes.

Build: Handles building actions, such as placing roads and settlements.

DevelopmentCard: Manages the development cards, including buying, trading, and using them.

## Class: Catan
The Catan class is responsible for managing the game's flow, including player turns, dice rolling, trading, and ending the game. It initializes the board and players, handles game events, and determines the winner.

Catan(Player& p1, Player& p2, Player& p3, bool run=true): Constructor that initializes the game with three players and optionally starts the game.

~Catan(): Destructor that cleans up any dynamically allocated resources.

void placeFirstRoadSettlement(const string& firstOrSecond): Handles the initial placement of roads and settlements for each player.

void runGame(): Starts the game, manages the initial setup, and begins the turn rotation.

void runTurn(bool first = false): Manages a player's turn, including the options to build, trade, and use development cards.

int rollDice(): Simulates rolling two dice and handles the resulting actions, such as distributing resources.

unsigned int chooseNum(): Securely prompts the user for a number input, ensuring valid input.

Player& choosePlayer(): Prompts the current player to choose another player for trading or other interactions.

void tradeResources(): Manages the resource trading process between players.

bool agreeToTrade(string playerName): Prompts a player to agree or disagree with a trade offer.

void tradeDevelopmentCard(): Manages the process of trading development cards between players.

bool agreeToDevelopmentTrade(string playerName): Prompts a player to agree or disagree with a development card trade offer.

void nextTurn(): Advances the game to the next player's turn.

void endGame(): Ends the game and displays the final scores of all players.

## Class: Board
The Board class represents the game board, including the tiles, paths, and nodes. It manages the ownership of paths and nodes and provides methods for interacting with the board.

vector<pair<string, int>> Tiles: A vector of tiles, each represented by a pair of a resource type and a number.

vector<string> pathsOwners: A vector that tracks the ownership of paths on the board.

vector<string> nodesOwners: A vector that tracks the ownership of nodes on the board.

vector<vector<unsigned int>> tilesAdjacentNodes: A nested vector that maps each node to its adjacent tiles.

vector<pair<unsigned int, unsigned int>> NodesAdjacentPaths: A vector that maps each path to its adjacent nodes.




הסבר כללי על המחלקות:

מימוש של משחק קטאן באמצעות המחלקות:

Player.hpp and Player.cpp: 
מחלקה בה יש את כל הפרטים על שחקן (שם, רשימת שבילים, נכסים, קלפים, כמות נקודות..) 
והמתודות שקשורות לשחקן (הורדת קלפים במקרה שיוצא 7 בקוביות, החלפת קלפי משאב, הוספת קלפי פיתוח, הדפסת הקלפים שלו..)


Build.hpp and Build.cpp:
מחלקה עם מתודות בנייה בלוח עבור שחקן מסוים כמו בניית דרך, ביטול דרך, בניית יישוב ובניית עיר.


DevelopmentCard.hpp and DevelopmentCard.cpp:
מחלקה המממשת את קלפי הפיתוח והמתודות שקשורות אליהם כמו החלפה של קלפי פיתוח, שימוש בקלף פיתוח..


Board.hpp and Board.cpp:
מחלקה לבניית לוח משחק, מוגדרות בה רשימת שכנויות של קודקודים לאריחים ורשימת שכנויות של קודקודים לכל שביל, על מנת שנוכל לבדוק בכל מהלך בניה אם הוא חוקי.
יש בה גם רשימה של הקודקודים והדרכים ומי הבעלים של כל אחת מהן (אם אין אז none)


Catan.hpp and Catan.cpp:
אחראית להרצה הכללית של המשחק בשילוב עם שאר המחלקות. יש אפשרות לבחור משחק עם הרצה דינמית ויש אפשרות לבחור במשחק עם קוד סטטי כמו בtests.
במשחק דינמי, בכל תור השחקן מקבל רשימת מהלכים אפשריים וצריך לבחור, המשחק יסתיים כששחקן יגיע ל10 נקודות או כשאחר השחקנים יבחר לסיים את המשחק.


בקובץ Demo יש התחלה של הרצה של משחק, בו הלוח נבנה בצורה רנדומלית.

בקובץ Tests ההרצות הן על לוח בו האריחים והמספרים קבועים (כמו באיור בהוראות המשחק) וביצוע המשחק הוא סטטי.

![image](https://github.com/user-attachments/assets/a3d5a6ae-0116-4a43-a36c-0931847188b6)

ההתייחסות לאריחים, לדרכים ולקודקודים היא באמצעות מספור של כולם כמו באיור המצורף.

![image](https://github.com/user-attachments/assets/e712c995-3ad0-4cb3-b42b-ff8798508c0c)


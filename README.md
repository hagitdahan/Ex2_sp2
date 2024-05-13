Name: hagit dahan
Email: hagitdahan101@gmail.com
Phone: 315158568
# מטלה 2 - גרפים והעמסת אופרטורים

הפעלה:
'make' לקמפל את התוכנית ולהריץ demo
'make test' קמפול הטסטים
'./test' הרצת הטסטים 


Graph.cpp
// מחלקה המייצגת גרף בונה אותו מאתחלת את המשתנים ומדפיסה אותו 

בנוסף ממשת את האופרטורים הבאים :
>,<,>=,<=,!=,==
G++,++G,G--,--G
<< output
G1+ unary
G1- unary
G1+G2
G1-G2
G1*G2
G1*a a scalar

`Graph::Graph()` :  מאתחלת את הגרף עם ערכים ברירת מחדל
-numOfVertices(0)- כמות קודקודים שווה ל-0 בהתחלה
-numEdges(0)- כמות צלעות בהתחלה שווה לאפס
-adjancencyMatrix()- מטריצת השכנויות המייצגת את הגרף
-graphType(GraphType::UNDIRECTED)- מאתחלת את תכונת הגרף המכוון כדיפולא לא מכוון
-weightType(WeightType::UNWEIGHTED)- מאתחלת את הגרף כלא ממשוקל באופן דיפולטיבי
-edgeType(EdgeType::NON_NEGATIVE)- מאתחלת את תכונת המאפשרת משקלים שליליים כלא מאפשרת


`void Graph::loadGraph(const vector<vector<int>> &matrix);` :  טוען את הגרף ממטריצת שכנות שמועברת כפרמטר בצורת מטריצה דו-מימדית. פונקציה זו מאתחלת את מטריצת השכנויות של הגרף ומעדכנת את מספר הקודקודים והצלעות בהתאם.

`string printGraph() const;`: מחזירה מחרוזת המייצגת את מטריצת השכוניות

`friend std::ostream& operator<<(std::ostream& out,const Graph &g);`:printGraph()פונקציה שעושה העמסה לאופרטור >> פלט משתמשת ב

`Graph operator+(const Graph& otherGraph)const;`: פונקציה המבצעת העמסה לאופרטור + בין שתי מטריצות

`Graph operator+() const;`:פונקציה מבצעת אופרטור + אונרי

`Graph operator+=(const Graph& otherGraph);`:פונקציה המבצעת העמסה לאופרטור += בין שתי מטריצות

`Graph operator-(const Graph& otherGraph)const;`:פונקציה המבצעת העמסה לאופרטור - בין שתי מטריצות

`Graph operator-() const;`:פונקציה מבצעת אופרטור - אונרי

`Graph operator-=(const Graph& otherGraph);`:פונקציה המבצעת העמסה לאופרטור -= בין שתי מטריצות

`bool operator>(const Graph& other) const;`: פונקציה מבצעת העמסת לאופרטור >

`bool operator>=(const Graph& other) const;` :: פונקציה מבצעת העמסת לאופרטור >=

`bool operator<(const Graph& other) const;`: פונקציה מבצעת העמסת לאופרטור <

`bool operator<=(const Graph& other) const;`: פונקציה מבצעת העמסת לאופרטור <=

`bool operator!=(const Graph& other) const;`: פונקציה מבצעת העמסת לאופרטור !=

`bool operator==(const Graph& other) const;`: פונקציה מבצעת העמסת לאופרטור ==

`Graph& operator++();`:פונקציה מבצעת העמסת לאופרטור (G++)

`Graph operator++(int);`:פונקציה מבצעת העמסת לאופרטור (++G)

`Graph& operator--();`:פונקציה מבצעת העמסת לאופרטור (G--)

`Graph operator--(int);`:פונקציה מבצעת העמסת לאופרטור (--G)

`Graph operator*(const Graph& other) const;`:פונקציה המבצעת העמסת לאופרטור * בין גרפים

`Graph&operator*=(double number);`:פונקציה המבצעת העמסת לאופרטור * בין גרף לסקלר



Help Funcion:

`bool Graph::isValid(const vector<vector<int>>& matrix);`: פונקצייה הבודקת האם המטריצה שהתקבלה ריבועית אחרת מחזיר שגיאה

`bool sameSize(const Graph &other)const;`פונקציה המחזירה האם שתי מטריצות מכילות כמות זהה של קודקודים כלומר מאותו סדר גודל :

`bool isContaine(const Graph& other) const;`: פונקציה המחזירה האם הגרף מלקה מכיל את גרך other 


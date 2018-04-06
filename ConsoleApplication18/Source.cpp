#include "shortest_path.h"
int transform(string x)
{
	int sz = x.length();
	int ans = 0;
	int i;
	bool negative = 0;
	if (x[0] == '-'){ i = 1; negative = 1; }
	else i = 0;
	for (; i < sz; i++)
	{
		if (x[i]<48 || x[i]>57)// number from 1 to 9 in ascii code
		{
			return NegInfinity;
		}
		else
		{
			ans += (int)(x[i] - 48);
			ans *= 10;
		}
	}
	ans /= 10;
	if (negative)
		return -1 * ans;
	else return ans;
}
int main()
{
	set<string>st;
	int NumCities, NumEdges;
	string ArrCity1[MAXSIZE], ArrCity2[MAXSIZE], ArrCities[MAXSIZE], x, z;
	int ArrCost[MAXSIZE], TheCost, cunt = 0;
	string inpt, inpt2;
	int cost, cost2,num;
	while (true)
	{// This Block Of Code Is For Getting Integres In a String To Avoid Bugs In Console
		cout << "please enter the number of cities .\n";
		cin >> inpt;
		if (transform(inpt) == NegInfinity)
		{
			cout << "Please Enter A Valid Nmuber\n";
			continue;
		}
		else
		{
			NumCities = transform(inpt); break;
		}
	}
	if (NumCities)cout << "\nPlease Enter the names of the cities \n";
	for (int i = 0; i < NumCities;)// i will increase only when the input is valid
	{
		cin >> x;
		if (st.count(x))
		{
			cout << "You Entered This City Before , Please Inter A New One \n";
			continue;
		}
		else
		{
			st.insert(x);
			++i;
		}
	}
	while (true)
	{// This Block Of Code Is For Getting Integres In a String To Avoid Bugs In Console
		cout << "please enter the number of edges .\n";
		cin >> inpt;
		if (transform(inpt) == NegInfinity)
		{
			cout << "Please Enter A Valid Nmuber\n";
			continue;
		}
		else
		{
			NumEdges = transform(inpt); break;
		}
	}
	cout << "\nEnter The First City Then The Second City Then The Cost Of the Edge \n";
	for (int i = 0; i < NumEdges;)// i will increase only when the input is valid
	{
		cin >> x >> z >> inpt;
		if (!st.count(x))
		{
			cout << "City One Isn't in the Cities You Entered ,Please Enter Valid Names \n";
			continue;
		}
		if (!st.count(z)){
			cout << "City Two Isn't in the Cities You Entered ,Please Enter Valid Names \n";
			continue;
		}
		if (transform(inpt) == NegInfinity){ cout << "Please Enter A Valid Cost \n"; continue; }
		else TheCost = transform(inpt);
		ArrCity1[i] = x, ArrCity2[i] = z, ArrCost[i] = TheCost;
		++i;
	}
	for (auto u : st) ArrCities[cunt++] = u;
	shortest_path f;
	f.Input(NumCities, NumEdges, ArrCities, ArrCity1, ArrCity2, ArrCost);
	while (true)
	{
		char u;
		string city1, city2;
		cout << "Please Enter number (1) if you want to update your Graph Or Show Path Between Two Cities \nOr (0) If You Want To Exit\n";
		cin >> u;
		if (u == '0') break;
		else if (u == '1')
		{
			while (true)
			{
				//f.TestShow();
				char ch;
				cout << "please enter the number of your choice :\n1 - Add edage between two cities\n2 - remove edge between two cities\n3 - update cost between two cities\n4 - remove city\n5 - Add a new city \n6 -show shortest path between two cities\n7 - if you finished \n";
				cin >> ch;
				if (ch == '8') break;
				else if (ch == '1')
				{

					while (true)
					{
						cout << "Please enter the two cities which you want to Add Edage between them then cost\n";
						cin >> city1 >> city2 >> inpt;
						if (!st.count(city1))
						{
							cout << "City One Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						if (!st.count(city2))
						{
							cout << "City Two Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						if (transform(inpt) == NegInfinity)
						{
							cout << "Please Enter A Valid Cost\n";
							continue;
						}
						else if (f.FindEdge(city1,city2,cost)==-1)
						{
							cost = transform(inpt);
							f.AddEdge(city1, city2, cost);
							break;
						}
					}
				}
				else if (ch == '2')
				{
					while (true)
					{
						cout << "Please enter the two cities which you want to Remove Edge between them Then The Cost Between These Two Cities \n";
						cin >> city1 >> city2 >> inpt;
						if (!st.count(city1))
						{
							cout << "City One Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						if (!st.count(city2))
						{
							cout << "City Two Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						if (transform(inpt) == NegInfinity)
						{
							cout << "Please Enter A Valid Cost\n";
							continue;
						}
						else
						{
							cost = transform(inpt);
						}
						if (f.FindEdge(city1, city2, cost) == -1)
						{
							cout << "There Is No Edge Between " << city1 << " And " << city2 << " With Cost " << cost << "\n"; continue;
						}
						else
						{
							f.RemoveEdge(city1, city2, cost);
						}
						break;
					}
				}

				else if (ch == '3')
				{
					while (true)
					{
						cout << "Please Enter The Two Cities You Want To Update Cost Between Them Then Enter The Old Cost Then The New Cost\n";
						cin >> city1 >> city2 >> inpt >> inpt2;
						if (!st.count(city1))
						{
							cout << "City One Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						if (!st.count(city2))
						{
							cout << "City Two Isn't in the Cities You Entered ,Please Enter Valid Names \n";
							continue;
						}
						cost = transform(inpt);
						cost2 = transform(inpt2);
						if (cost == NegInfinity)
						{
							cout << "Old Cost Isn't a Valid Number \n";
							continue;
						}
						if (cost == NegInfinity)
						{
							cout << "New Cost Isn't a Valid Number \n";
							continue;
						}
						if (f.FindEdge(city1, city2, cost) == -1)
						{
							cout << "There Is No Edge Between The Two Cities With Cost " << cost << "\n";
							continue;
						}
						f.UpdateCost(city1, city2, cost, cost2); break;
					}
				}
				else if (ch == '4')
				{
					while (true)
					{
						cout << "Please Enter The Name Of The City You Want To Remove From The Map \n";
						cin >> city1;
						if (!st.count(city1))
						{
							cout << "This City Isn't in the Cities You Entered \n";
							continue;
						}
						else
						{
							st.erase(city1);
							f.RemoveNode(city1);
							break;
						}
					}
				}
				else if (ch == '5')
				{
					while (true)
					{
						cout << "Please Enter The Name Of The City You Want To Add\n";
						cin >> x; 
						if (st.count(x))
						{
							cout << "This City Is Already Added To The Map\n"; continue;
						}
						else
						{
							st.insert(x); f.AddCity(x); break;
						}
					}
					cout << "please Enter the number of cities that will be connected with the new city\n";
					while (true)
					{// This Block Of Code Is For Getting Integres In a String To Avoid Bugs In Console
						cin >> inpt;
						if (transform(inpt) == NegInfinity)
						{
							cout << "Please Enter A Valid Nmuber\n";
							continue;
						}
						else
						{
							num = transform(inpt); break;
						}
					}
					for (int i = 1; i <= num; ++i)
					{
						string nam;		
						while (true)
						{
							cout << "please enter the name of city number " << i << " and the cost between them\n";
							cin >> nam>>inpt;
							if (!st.count(nam))
							{
								cout << "This City Isn't in the Cities You Entered ,Please Enter Valid Names \n";
								continue;
							}
							if (transform(inpt) == NegInfinity)
							{
								cout << "Please Enter A Valid Cost\n";
								continue;
							}
							else
							{
								cost = transform(inpt); break;
							}
						    break;
						}
						f.AddEdge(x, nam, cost);
					}
				}
				else if (ch == '6')
				{
					while (true)
					{
						cout << "please enter two cities which you want to show The Shortest path between them And The Cost \n";
						cin >> x >> z;
						if (!st.count(x))
						{
							cout << "The First City Isn't In The Citis You Entered \n";
							continue;
						}
						if (!st.count(z))
						{
							cout << "The Second City Isn't In The Citis You Entered \n";
							continue;
						}
						if (x == z)
						{
							cout << "The Path From a City To The Same City Costs 0 \n";
							break;
						}
						cout << "please choose which algo you want to show path using it :\n1 - Dijkstra if your haven't negative edges\n2 - shortest path faster algo to all kinds of graphs\n3 - Bellman ford\n4 - floyd warshall\n5 - if want all algos\n";
						char c; cin >> c;
						if (c == '1' )
						{
							f.algos(x, z, 1);
							break;
						}
						else if (c == '2')
						{
							f.algos(x, z, 2);
							break;
						}
						else if (c == '3' )
						{
							f.algos(x, z, 3);
							break;
						}
						else if (c == '4' )
						{
							f.algos(x, z, 4);
							break;
						}
						else if (c == '5')
						{
							f.algos(x, z, 5);
							break;
						}
						else if (c == '0')break;
						else
						{
							cout << "Please Enter A Valid Input \n"; 
							continue;
						}
					}
				}
				else if (ch == '7')break;
				else
				{
					cout << "Please Enter A Valid Input \n"; 
						
				}
			}
		}
		else
		{
			cout << "Unvalid Input \n";
		}
	}
	system("pause");
	return 0;
}
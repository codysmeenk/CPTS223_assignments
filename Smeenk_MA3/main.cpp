#include <map>
#include "generateUsers.hpp"

using namespace std;

map<string, User> buildMapByUserName(vector<User> users) {
	map<string, User> usersMap;
	
	for (const auto& user : users) {
		usersMap[user.userName] = user;
	}

	return usersMap;
}

map<string, User> buildMapByEmail(vector<User> users) {
	map<string, User> usersMap;
	
	for (const auto& user : users) {
		usersMap[user.email] = user;
	}

	return usersMap;
}

void printMap(map<string, User> aMap) {
	int index = 0;

	for (const auto& pair : aMap) {
		cout << "#" << index << ". Key: " << pair.first << ", Value: ";
		cout << pair.second.userName << ","
			<< pair.second.lastName << ","
			<< pair.second.firstName << ","
			<< pair.second.email << ","
			<< pair.second.numPosts << ","
			<< pair.second.mostViewedCategory << endl;

		index++;
	}
}

bool isMapSorted(map<string, User> aMap) {
	if (aMap.empty()) {
		return true;
	}

	auto it = aMap.begin();
	auto prevKey = it->first;
	++it;

	for (; it != aMap.end(); ++it) {
		if (it->first < prevKey) {
			return false;
		}

		prevKey = it->first;
	}
	
	return true;
}

bool testSearchByKey(map<string, User> aMap, string keyToSearch) {
	auto it = aMap.begin();
	
	while (it != aMap.end()) {
		if (it->first == keyToSearch) {
			return true;
		}
		++it;
	}

	return false;
}

bool testDeleteByKey(map<string, User> aMap, string keyToDelete) {
	auto it = aMap.begin();

	while (it != aMap.end()) {
		if (it->first == keyToDelete) {
			aMap.erase(it);
			return true;
		}
		++it;
	}

	return false;
}

void printActiveUsers(map<string, User> aMap) {
	int activeThreshold = 800;
	auto it = aMap.begin();

	while (it != aMap.end()) {
		if (it->second.numPosts > activeThreshold) {
			cout << it->second.userName << endl;
		}

		++it;
	}
}

void printMostPopularCategory(map<string, User> aMap) {
	map<string, int> categoryCount;

	for (const auto& pair : aMap) {
		categoryCount[pair.second.mostViewedCategory]++;
	}

	string mostPopularCategory;
	int maxCount = 0;

	for (const auto& category : categoryCount) {
		if (category.second > maxCount) {
			maxCount = category.second;
			mostPopularCategory = category.first;
		}
	}

	cout << "Most Popular Category: " << mostPopularCategory << endl;
}

int main()
{
	int numUsers = 10;
	vector<User> users = generateUsers(numUsers);

	cout << "Build map with username as key" << endl;
	map<string, User> mapByUserName = buildMapByUserName(users);
	if (mapByUserName.size() == numUsers)
		cout << " Built successfully." << endl << endl;
	else
		cout << " Built unsuccessfully." << endl << endl;
	cout << "Print \"mapByUserName\" map:" << endl;
	printMap(mapByUserName);
	cout << endl;

	string keyToSearch = "smith55";
	cout << "Search by key: mapByUserName[\"" << keyToSearch << "\"]" << endl;
	if (testSearchByKey(mapByUserName, keyToSearch))
		cout << " Search successfully." << endl << endl;
	else
		cout << " Search unsuccessfully." << endl << endl;

	string keyToDelete = "smith55";
	cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
	if (testDeleteByKey(mapByUserName, keyToDelete))
		cout << " Delete successfully." << endl << endl;
	else
		cout << " Delete unsuccessfully." << endl << endl;

	cout << "Test if map's key is sorted" << endl;
	if (isMapSorted(mapByUserName))
		cout << " Order test passed!" << endl << endl;
	else
		cout << " Order test failed!" << endl << endl;

	cout << "Print usernames with more than 800 tweets:" << endl;
	printActiveUsers(mapByUserName);
	cout << endl;

	cout << "Print the most popular category" << endl;
	printMostPopularCategory(mapByUserName);
	cout << endl;

	cout << "============================================================================== " << endl << endl;
	
	cout << "Build map with username as key" << endl;
	map<string, User> mapByEmail = buildMapByEmail(users);
	if (mapByEmail.size() == numUsers)
		cout << " Built successfully." << endl << endl;
	else
		cout << " Built unsuccessfully." << endl << endl;

	keyToSearch = "kat@gmail.com";
	cout << "Search by key: mapByEmail[\"" << keyToSearch << "\"]" << endl;
	if (testSearchByKey(mapByEmail, keyToSearch))
		cout << " Search successfully." << endl << endl;
	else
		cout << " Search unsuccessfully." << endl << endl;

	keyToDelete = "kat@gmail.com";
	cout << "Delete by key: \"" << keyToDelete << "\"" << endl;
	if (testDeleteByKey(mapByEmail, keyToDelete))
		cout << " Delete successfully." << endl << endl;
	else
		cout << " Delete unsuccessfully." << endl << endl;
	return 0;
}
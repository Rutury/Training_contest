#include <iostream>
#include <unordered_map>
#include <unordered_set>

using namespace std;
constexpr int MAX_INGREDIENTS = 1000000000;

class TRecipe {
public:
    int canCook; // -1 cant, 0 unknown, 1 can
    long long A;
    long long B;

    TRecipe() : canCook(0), A(0), B(0) {}
    TRecipe(int canCook, long long A, long long B) : canCook(canCook), A(A), B(B) {}
};

class TMagicBook {
public:
    unordered_map<int, TRecipe> recipes;
    unordered_map<int, unordered_map<int, int>> ingredients;

    void cinRecipes() {
        int N;
        cin >> N;
        recipes.reserve(N);
        recipes[1] = TRecipe(1, 1, 0);
        recipes[2] = TRecipe(1, 0, 1);
        for (int i = 3; i <= N; i++) {
            recipes[i] = TRecipe();
            int k, ingredient;
            cin >> k;
            for (int j = 0; j < k; j++) {
                cin >> ingredient;
                if (ingredient == 1) recipes[i].A++;
                else if (ingredient == 2) recipes[i].B++;
                else ingredients[i][ingredient]++;
            }
            if (ingredients.count(i) == 0) recipes[i].canCook = 1;
        }
    }

    int tryToCook(int recipeID) {
        unordered_set<int> recipeQueue;
        return tryToCookRecurcive(recipeID, recipeQueue);
    }

    int tryToCookRecurcive(int recipeID, unordered_set<int>& recipeQueue) {
        TRecipe& curRecipe = recipes[recipeID];
        if (curRecipe.canCook != 0) return curRecipe.canCook;
        if (recipeQueue.count(recipeID) > 0) return -1;
        recipeQueue.insert(recipeID);

        for (auto& pair : ingredients[recipeID]) {
            TRecipe& ingredient = recipes[pair.first];
            int ingredientAmount = pair.second;
            if (ingredient.canCook == 0) ingredient.canCook = tryToCookRecurcive(pair.first, recipeQueue);
            if (ingredient.canCook == 1) {
                curRecipe.A += ingredient.A * ingredientAmount;
                curRecipe.B += ingredient.B * ingredientAmount;
                if (curRecipe.A > MAX_INGREDIENTS || curRecipe.B > MAX_INGREDIENTS) {
                    curRecipe.canCook = -1;
                    return -1;
                }
            } else {
                curRecipe.canCook = -1;
                return -1;
            }
        }
        return 1;
    }

    bool canCook(int recipeID, long long A, long long B) {
        TRecipe& recipe = recipes[recipeID];
        if (recipe.canCook == 0) recipe.canCook = tryToCook(recipeID);
        if (recipe.canCook == 1 && recipe.A <= A && recipe.B <= B) return true;
        return false;
    }
};


int main() {
    TMagicBook myMagicBook;
    myMagicBook.cinRecipes();
    int Q;
    cin >> Q;
    for (int i = 0; i < Q; i++) {
        long long A, B;
        int potionID;
        cin >> A >> B >> potionID;
        cout << (myMagicBook.canCook(potionID, A, B) ? 1 : 0);
    }
    cout << endl;
}

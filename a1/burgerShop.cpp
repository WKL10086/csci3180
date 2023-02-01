// submit this file

#include "burgerShop.h"
#include "bun.h"
#include "meat.h"
#include <iostream>
using std::cout;
using std::endl;

BurgerShop::BurgerShop(int ingredientStorageCapacity) : ingredientStorageCapacity(ingredientStorageCapacity)
{
    ingredientStorage = new Ingredient *[ingredientStorageCapacity]; // create a dynamic array of Ingredient pointers, of size ingredientStorageCapacity
    for (int i = 0; i < ingredientStorageCapacity; i++)              // we should set all ingredientStorage slots to nullptr's since our storage is literally empty at the beginning
        ingredientStorage[i] = nullptr;
}

BurgerShop::~BurgerShop()
{
    // TODO: implement this function
    // Hint: use "delete" for non-array dynamic objects, and use "delete []" for dynamic arrays

    for (int i = 0; i < ingredientStorageCapacity; i++)
    {
        delete ingredientStorage[i];
    }

    delete[] ingredientStorage;
}

void BurgerShop::attemptToMakeBun(int softness)
{
    bool result = makeBun(softness); // makeBun will return false if our storage is full
    if (result)
        cout << "Bun (" << softness << "% soft) made and added to storage! :)";
    else
        cout << "Whoops! No more storage space for the new bun! :(";
    cout << endl
         << endl;
}

void BurgerShop::attemptToMakeMeat(int doneness)
{
    bool result = makeMeat(doneness); // makeMeat will return false if our storage is full
    if (result)
        cout << "Meat (" << doneness << "% done) cooked and added to storage! :)";
    else
        cout << "Whoops! No more storage space for the new meat! :(";
    cout << endl
         << endl;
}

void BurgerShop::attemptToMakeAndServeBurger(int requiredBunSoftness, int requiredMeatDoneness)
{
    bool result = makeAndServeBurger(requiredBunSoftness, requiredMeatDoneness); // makeAndServeBurger will return false if there are not enough suitable ingredients
    if (result)
        cout << "A burger has been happily crafted and served! :)";
    else
        cout << "Oh no, we cannot craft the burger requested! :(";
    cout << endl
         << endl;
}

bool BurgerShop::isStorageFull()
{
    return ingredientStorageUsed == ingredientStorageCapacity;
}

void BurgerShop::addFoodToStorage(Ingredient *food)
{
    for (int i = 0; i < ingredientStorageCapacity; i++)
    {
        if (ingredientStorage[i] == nullptr) // check if we have found the first non-empty storage slot
        {
            ingredientStorage[i] = food; // add the ingredient to that slot then
            break;                       // this is important to stop our loop here: what would happen if we don't?
        }
    }
    ingredientStorageUsed++; // update the state
}

bool BurgerShop::makeBun(int softness)
{
    if (isStorageFull()) // cannot make new buns when the storage is full
        return false;
    addFoodToStorage(new Bun(softness)); // actually make it and store it
    return true;
}

bool BurgerShop::makeMeat(int doneness)
{
    if (isStorageFull()) // cannot make new meats when the storage is full
        return false;
    addFoodToStorage(new Meat(doneness)); // actually make it and store it
    return true;
}

bool BurgerShop::makeAndServeBurger(int requiredBunSoftness, int requiredMeatDoneness)
{
    // TODO: implement this function
    /*
        Hint:
        ingredientStorage[i] is merely an Ingredient pointer.
        Therefore, you cannot directly use it like a Bun pointer even though the object it points to is actually a Bun object. For example, the following won't compile:
            cout << ingredientStorage[i]->getSoftness() << endl;
        In C++, you can use dynamic_cast for trying to cast it to a Bun pointer like this:
            Bun* realBunPointer = dynamic_cast<Bun*>(ingredientStorage[i]);
        The good thing about dynamic_cast is that it would give you a nullptr if the casting fails when ingredientStorage[i] doesn't really point to a Bun object. It is useful for checking what object it is pointing to. Of course, before you do dynamic_cast, you should make sure ingredientStorage[i] is not really a nullptr itself first.
    */

    // A Happy Teemo Burger uses exactly 1 suitable meat and 2 suitable buns. If we cannot gather from the storage all those 3 specific ingredients for a burger, the function will simply return false.
    // Regarding what the suitable ingredients are:
    // Spoiled ingredients should never be used. By the way, they just stay in the storage forever because Teemo is apparently too busy. Don't help him to remove those spoiled stuff yourself.
    // A suitable meat must have at least requiredMeatDoneness of doneness.
    // A suitable bun must have at least requiredBunSoftness of softness.
    // When looking for each of those 3 ingredients, Teemo simply always picks the first suitable meat and first two suitable buns from the storage - i.e. technically, the smaller the array index the better for each of them.
    // After we have found the 3 suitable ingredients, we do the following to actually craft and serve the burger:
    // Remove the used ingredients from the storage. That means you should dynamically deallocate the 1 dynamic Meat object and the 2 dynamic Bun objects, and then for each of them set the corresponding ingredientStorage[i] to nullptr indicating that the originally-occupied storage slot is now empty and thus reusable later for new ingredients.
    // Since 3 ingredients have been used, decrease ingredientStorageUsed by 3.
    // Add 1 to burgerServed as our now-satisfied customer walks away with our burger happily.
    // Return true.
}

void BurgerShop::update()
{
    // update the states for each of the ingredients stored
    for (int i = 0; i < ingredientStorageCapacity; i++)
        if (ingredientStorage[i] != nullptr) // of course, we have to make sure the current storage slot is not really empty
            ingredientStorage[i]->update();  // so update it
}

void BurgerShop::print()
{
    cout << "Currently, we have " << ingredientStorageUsed << " ingredient" << (ingredientStorageUsed != 1 ? "s" : "") << " in the shop storage: " << endl;
    for (int i = 0; i < ingredientStorageCapacity; i++) // go through our whole ingredient storage
    {
        cout << "Slot " << i << ": ";
        if (ingredientStorage[i] == nullptr) // nullptr means an empty slot at index i
            cout << "empty";
        else
            ingredientStorage[i]->print(); // invoke the print function for the ingredient - it will call the correct function (Bun's or Meat's) depending on the actual class of the object the pointer points to: it is a dynamic binding
        cout << endl;
    }
    cout << "And... " << burgerServed << " Happy Teemo Burger" << (burgerServed != 1 ? "s" : "") << " proudly served so far!" << endl;
    cout << endl;
}

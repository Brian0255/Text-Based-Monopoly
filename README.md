# Text-Based-Monopoly
This is a text-based(CLI) version of Monopoly with many features, some not present in the original game.

![](/pictures/boardpicture.png)
## The General Rules
  - Like original Monopoly, you are trying to win by making every other player go bankrupt, in ways such as:
    - Buying property you land on and collecting rent from other players.
    - Building houses/hotels on your property to increase the rent.
    - Collecting money from other players through the use of chance/community/collectable cards.
    - Taking other players' money by winning battles against them and defending against property attacks.
    - Trading property with other players to try and own sets.
    
    
## Features
- ### Playing Against AI
  - Players may choose to play against one or several AI. AI will make several decisions, such as:
    - Mortgaging property if they are low on cash.
    - Building houses/hotels/turrets on their property.
    - Participating in property auctions.
    - Declining/accepting player trade offers.
    - Deciding whether or not to purchase property.
    
- ### Collectable Cards
  - Besides community and chest cards, there is a new type of card you you can get, a "Collectable" card. 
  - Collectable cards are given at random when you pick up a community or chest card, with a 50% chance.
  - This card is held by the player and can be used at the start of their turn, with random effects such as:
    - Granting you $25, $50, or $100 from the bank.
    - Granting you $25, $50, or $100 from a random player.
    - Doubling your next roll.
    - Getting you out of jail.
  
- ### Property Trading
  - Before you roll, you can ask players to trade properties with you. It works as follows:
    1. You select the properties you're offering from a list.
    2. You select properties you want from the other player.
    3. The other player then accepts or declines your offer.
        - An example after selections: 
      
          ![exampleOffer](/pictures/exampleTradeOffer.png)
- ### Player Battles
  - Landing on the same spot as 1 or more players will pit you against one of them in a battle.
  - Battles are turn-based and automated. Each player's HP is determined by the assets they own.
  - The player that loses will give 20% of their current cash to the other player.
  - An example of a battle turn: 
    
    ![exampleBattleTurn](/pictures/playerBattleTurnExample.png)
- ### Property Battles
  - If you land on someone else's property, you don't have to pay rent! Instead, you can choose to attack it. If you win, you can just pay twice the cost of the property (which may be cheaper than the rent in some cases).
  - Attacking property will pit you against the "mob" that defends the property.
  - The battling is the exact same as player battles, except the turret on the property can also attack. Likewise, if the player has turrets built on the property, it will be much more difficult.
  - Losing means you lose 30$ of your cash.
  
- ### Property Auctioning
  - Similar to original monopoly, a property will automatically be put up for auction if the player that landed on it doesn't want it.
  - Bidding will continue until someone's bid is outmatched. After that, they will own the property.
  - AI will participate too! However, they have limits to what they'll bid, and will back out if they think it's not worth it.
  - Some examples of what bidding looks like:
  
    ![](/pictures/bidStartExample.png) \
    ![](/pictures/bidExample2.png) \
    ![](/pictures/AIBid.png)
  
- ### Building
  - What would Monopoly be without building houses, hotels, and of course, turrets! This game will let you do all of that.
  #### Building Houses
    - Just like Monopoly, you can build houses on any set that you own.
    - Also like Monopoly, you must build evenly, up to 4 houses per property in the set.
    - Once you have 4 houses per property in the set, you can then build hotels.
    
  #### Building Hotels
    - Hotels are great for making your opponents go bankrupt! However, building one isn't so easy. These are the requirements:
      1. You must own every property in the set(such as Mediterranean Ave and Baltic Ave).
      2. Each property must have 4 houses built in the set.
    - Once these requirements are met, you can then build 1 hotel per property. They only cost as much as a house.
    
  #### Building Turrets
    - Building turrets are a completely new feature in this version of Monopoly.
    - Like you would think, turrets are specifically meant to defend property in case of a property attack. They are very powerful!
    - You only need to own the property to build a turret, making them a greate defensive play if you feel it's necessary.
    - Turrets also give you extra HP when you are in any battle.
    
- ### Warping
  - If you've managed to grab every railroad, you can warp at the start of your turn!
  - You can warp to any other railroad you own.
  - You can only do this once per turn.
  
- ### Chance and Community Cards
  - Chance and Community Chest cards have many effects in this game, such as:
      - A 2% chance to go completely bankrupt.
      - Being warped back various amounts of spaces.
      - A 1% chance to receive 1000 dollars.
      - Advancing to go and collecting $200.
      - Losing and gaining various amounts of money.
      - Instantly being sent to jail.
      
- ### Cheats
  - Want to just play around with the game in a sandbox fashion? Various cheats before the game starts will let you do that, such as:
    - Giving everyone in the game 1 million dollars.
    - Forcing every roll to be doubles.
    - Forcing every roll to be a 1 and 2.
    - Assigning all property randomly.
    - Assigning all property to player 1.
    
- ### Property Mortgaging
  - Low on cash? Maybe it's time to mortgage a property. Like Monopoly, you can mortgage a property for half the value.
  - Mortgaging a property means you can't build houses, hotels, or turrets. You also can't charge anyone rent.
  - Mortgaged property is also unable to be attacked by another player if they land on it.
  - You can lift mortgages as well! However, it will cost an addition 10% interest to do so.
      
      

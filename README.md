![sdkhero](https://github.com/Elixir-Games-XYZ/elixir-unreal-sdk/assets/1970424/fbb21035-cad1-402d-bb19-224b161dc377)

# Welcome to Elixir Unreal SDK

## 1. Prepare Elixir

This steps validates that the game is being executed inside the Elixir Launcher Environment. If this step is completed successfully, the SDK will obtain the user session credentials, and from now on, the user will be logged into the game using his Elixir Launcher account.
If this step is not completed, the game wont be able to be executed, avoiding the game execution outside the Elixir Launcher or blocking Banned users.

### 1.1 Set your credentials

Get your credentials in the [Elixir Developer Dashboard](https://dashboard.elixir.app/) and add them to your project.

![Screenshot 2023-01-10 at 13 29 51](https://user-images.githubusercontent.com/61213914/211552137-1cc67b4a-5846-4b7b-983d-d89621d31fe2.png#center)


## 2. Get User Data

Once the user is authenticated, you will be able to execute this feature of the SDK, where we provide all elixir-related user information:

 - ElixirID: Unique and immutable user identification inside the Elixir Platform.
 - Username: Elixir user nickname, that can be displayed inside the game
 - Wallet: User wallet associated with the game blockchain network.

If your game already has a User entity, with account credentials, we recommend adding a "Link Account" button, that pairs up the ElixirID with your User Entity, so it's only needed to do it once. This way, each user will be able to use his native game account when launching from Elixir with just a one-time login.

## 3. Get Colletions

After referencing the NFT collections that the game includes using the Elixir Dashboard. You will be able to use this endpoint, which will provide all the NFTs that the user owns of these collections.
From now on, the game will need to stick to a unique identifier of each NFT as the tokenId, and match internally each tokenId with the in-game Visual representation for it.

![Screenshot 2023-01-10 at 13 32 07](https://user-images.githubusercontent.com/61213914/211552553-48317c33-55bc-416e-ae19-fc664fbf8727.png#center)

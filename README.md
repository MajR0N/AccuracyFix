<h1 align="center">Counter-Strike 1.6 Accuracy Fix</h1>
<p align="center">Counter-Strike 1.6 Accuracy Fix Plugin for MetaMod and ReGameDLL_CS</p>

<p align="center">
    <a href="https://github.com/SmileYzn/AccuracyFix/issues"><img alt="GitHub Issues" src="https://img.shields.io/github/issues-raw/smileyzn/AccuracyFix?style=flat-square"></a>
    <a href="https://github.com/SmileYzn/AccuracyFix/actions"><img alt="GitHub Workflow Status" src="https://img.shields.io/github/actions/workflow/status/SmileYzn/AccuracyFix/build.yml?branch=main&label=Build&style=flat-square"></a>
</p>

<h3>About Plugin</h3>
<p>This works with TraceLine function from Half-Life Engine, and scales the spread of every bullet toward the exact aim direction (recoil is kept).</p>
<p>The multiplier is set per weapon and per player state (standing, moving, ducking, in air).</p>

<h3>ReHLDS / ReGameDLL_CS</h3>
<p>
    This metamod plugin runs on latest action build of ReHLDS / ReGameDLL_CS versions!
    <br>
    <br>To download latest ReHLDS: <a href="https://github.com/dreamstalker/rehlds/actions?query=branch%3Amaster+is%3Asuccess+event%3Apush">Lastest Action (Master Builds) of ReHLDS here</a>
    <br>To download latest ReGameDLL_CS: <a href="https://github.com/s1lentq/ReGameDLL_CS/actions?query=is%3Asuccess+branch%3Amaster+event%3Apush">Lastest Action (Master Builds) of ReHLDS here</a>
</p>

------

<h3>Settings and variables</h3>

<details>
    <summary>Click to open</summary>
    
    // Spread multiplier of ALL weapons
    // >= 0 overrides every per weapon value below, -1.0 = use the per weapon values
    // 1.0 = vanilla spread (fix off), 0.55 = 45% less spread, 0.0 = no spread
    //
    // Default "-1.0"
    //
    af_spread_all "-1.0"
    
    // Spread multiplier per player state (0.0 - 2.0), multiplied with the weapon value
    // 1.0 = leave the weapon value as is, 0.0 = no spread in that state, 2.0 = double the spread
    // A player is in exactly one state: air > walking (shift) > moving > ducking > standing
    //
    // Default "1.0"
    //
    af_spread_stand "1.0"
    af_spread_walk "1.0"
af_spread_move "1.0"
    af_spread_duck "1.0"
    af_spread_air "1.0"
    
    // Spread multiplier of each weapon
    // 1.0 = vanilla spread (fix disabled for that weapon)
    // The AWP is only fixed while scoped (no-scope AWP keeps vanilla spread)
    //
    // Default "0.55"
    //
    af_spread_weapon_ak47 "0.55"
    af_spread_weapon_aug "0.55"
    af_spread_weapon_awp "0.55"
    af_spread_weapon_deagle "0.55"
    af_spread_weapon_elite "0.55"
    af_spread_weapon_famas "0.55"
    af_spread_weapon_fiveseven "0.55"
    af_spread_weapon_g3sg1 "0.55"
    af_spread_weapon_galil "0.55"
    af_spread_weapon_glock18 "0.55"
    af_spread_weapon_m249 "0.55"
    af_spread_weapon_m3 "1.0"
    af_spread_weapon_m4a1 "0.55"
    af_spread_weapon_mac10 "0.55"
    af_spread_weapon_mp5navy "0.55"
    af_spread_weapon_p228 "0.55"
    af_spread_weapon_p90 "0.55"
    af_spread_weapon_scout "0.55"
    af_spread_weapon_sg550 "0.55"
    af_spread_weapon_sg552 "0.55"
    af_spread_weapon_tmp "0.55"
    af_spread_weapon_ump45 "0.55"
    af_spread_weapon_usp "0.55"
    af_spread_weapon_xm1014 "1.0"

</details>

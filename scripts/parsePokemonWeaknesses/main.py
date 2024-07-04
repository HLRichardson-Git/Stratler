from bs4 import BeautifulSoup

html = """
<!-- Your provided HTML here -->
<tr class="has-pkmn" data-type1="18" data-type2="0">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-null type-cell">—</a> </div>
</th>
<td class="cell-num cell-total">21</td>
<td title="Normal &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="1">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-normal type-cell">Normal</a> </div>
</th>
<td class="cell-num cell-total">5</td>
<td title="Normal &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Poison &#8594; Fairy/Normal = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Normal = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Normal = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dragon &#8594; Fairy/Normal = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Normal = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Normal = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Normal = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="no-pkmn" data-type1="18" data-type2="2">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-fire type-cell">Fire</a> </div>
</th>
<td class="cell-num cell-total">0</td>
<td title="Normal &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Water &#8594; Fairy/Fire = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Electric &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fighting &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Fire = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Fire = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Flying &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Fire = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ghost &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Fire = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Fire = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fairy &#8594; Fairy/Fire = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="3">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-water type-cell">Water</a> </div>
</th>
<td class="cell-num cell-total">4</td>
<td title="Normal &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Water &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Electric &#8594; Fairy/Water = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Grass &#8594; Fairy/Water = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ice &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fighting &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Water = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Water = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Water = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fairy &#8594; Fairy/Water = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="4">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-electric type-cell">Electric</a> </div>
</th>
<td class="cell-num cell-total">2</td>
<td title="Normal &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Electric = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Grass &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Electric = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Electric = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Electric = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Flying &#8594; Fairy/Electric = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Psychic &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Electric = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Electric = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Electric = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fairy &#8594; Fairy/Electric = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="5">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-grass type-cell">Grass</a> </div>
</th>
<td class="cell-num cell-total">5</td>
<td title="Normal &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Grass = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Water &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Electric &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Grass &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Grass = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fighting &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Grass = super-effective" class="type-fx-cell type-fx-400">4</td> <td title="Ground &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Flying &#8594; Fairy/Grass = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Psychic &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Rock &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Grass = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Grass = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Grass = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Grass = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="6">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-ice type-cell">Ice</a> </div>
</th>
<td class="cell-num cell-total">1</td>
<td title="Normal &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Ice = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Water &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Ice = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fighting &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Poison &#8594; Fairy/Ice = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Ice = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Ice = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ghost &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Ice = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Ice = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Ice = super-effective" class="type-fx-cell type-fx-400">4</td> <td title="Fairy &#8594; Fairy/Ice = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="7">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-fighting type-cell">Fighting</a> </div>
</th>
<td class="cell-num cell-total">1</td>
<td title="Normal &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Fighting = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Fighting = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Fighting = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Psychic &#8594; Fairy/Fighting = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Bug &#8594; Fairy/Fighting = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Fighting = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ghost &#8594; Fairy/Fighting = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Fighting = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Fighting = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Steel &#8594; Fairy/Fighting = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Fighting = super-effective" class="type-fx-cell type-fx-200">2</td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="8">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-poison type-cell">Poison</a> </div>
</th>
<td class="cell-num cell-total">2</td>
<td title="Normal &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Poison = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Poison = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Poison &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ground &#8594; Fairy/Poison = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Flying &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Poison = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Bug &#8594; Fairy/Poison = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Poison = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Poison = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Poison = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Poison = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Poison = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> </tr>
<tr class="no-pkmn" data-type1="18" data-type2="9">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-ground type-cell">Ground</a> </div>
</th>
<td class="cell-num cell-total">0</td>
<td title="Normal &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Ground = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Electric &#8594; Fairy/Ground = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Grass &#8594; Fairy/Ground = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ice &#8594; Fairy/Ground = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fighting &#8594; Fairy/Ground = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ground &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Ground = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Ground = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ghost &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Ground = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Ground = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Ground = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Ground = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="10">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-flying type-cell">Flying</a> </div>
</th>
<td class="cell-num cell-total">4</td>
<td title="Normal &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Flying = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Grass &#8594; Fairy/Flying = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Flying = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fighting &#8594; Fairy/Flying = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Poison &#8594; Fairy/Flying = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Flying = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Flying &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Flying = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Flying = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ghost &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Flying = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Flying = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Flying = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Flying = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="11">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-psychic type-cell">Psychic</a> </div>
</th>
<td class="cell-num cell-total">10</td>
<td title="Normal &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Psychic = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Poison &#8594; Fairy/Psychic = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Psychic = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Bug &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Rock &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Psychic = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Dragon &#8594; Fairy/Psychic = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Steel &#8594; Fairy/Psychic = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Psychic = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="12">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-bug type-cell">Bug</a> </div>
</th>
<td class="cell-num cell-total">2</td>
<td title="Normal &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Bug = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Water &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Bug = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Bug = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Poison &#8594; Fairy/Bug = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Bug = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Flying &#8594; Fairy/Bug = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Psychic &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Bug = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Bug = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ghost &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Bug = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Bug = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Bug = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Bug = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="13">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-rock type-cell">Rock</a> </div>
</th>
<td class="cell-num cell-total">3</td>
<td title="Normal &#8594; Fairy/Rock = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fire &#8594; Fairy/Rock = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Water &#8594; Fairy/Rock = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Electric &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Rock = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ice &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Poison &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ground &#8594; Fairy/Rock = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Flying &#8594; Fairy/Rock = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Psychic &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Rock = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Rock = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Rock = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Rock = super-effective" class="type-fx-cell type-fx-400">4</td> <td title="Fairy &#8594; Fairy/Rock = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="14">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-ghost type-cell">Ghost</a> </div>
</th>
<td class="cell-num cell-total">2</td>
<td title="Normal &#8594; Fairy/Ghost = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Fire &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Ghost = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Poison &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ground &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Ghost = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Ghost = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Dragon &#8594; Fairy/Ghost = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Steel &#8594; Fairy/Ghost = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Ghost = normal effectiveness" class="type-fx-cell type-fx-100"></td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="15">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-dragon type-cell">Dragon</a> </div>
</th>
<td class="cell-num cell-total">1</td>
<td title="Normal &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Water &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Electric &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Grass &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Dragon = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fighting &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Poison &#8594; Fairy/Dragon = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Bug &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Rock &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Dragon = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Dragon = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Dragon = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Dragon = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Dragon = super-effective" class="type-fx-cell type-fx-200">2</td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="16">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-dark type-cell">Dark</a> </div>
</th>
<td class="cell-num cell-total">3</td>
<td title="Normal &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fire &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Water &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ice &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fighting &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Poison &#8594; Fairy/Dark = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Ground &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Flying &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Psychic &#8594; Fairy/Dark = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Bug &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Rock &#8594; Fairy/Dark = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Ghost &#8594; Fairy/Dark = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Dragon &#8594; Fairy/Dark = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Dark = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Steel &#8594; Fairy/Dark = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Fairy &#8594; Fairy/Dark = super-effective" class="type-fx-cell type-fx-200">2</td> </tr>
<tr class="has-pkmn" data-type1="18" data-type2="17">
<th>
<div class="cell-dual-type">
<a class="type-icon type-fairy type-cell">Fairy</a> <a class="type-icon type-steel type-cell">Steel</a> </div>
</th>
<td class="cell-num cell-total">8</td>
<td title="Normal &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fire &#8594; Fairy/Steel = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Water &#8594; Fairy/Steel = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Electric &#8594; Fairy/Steel = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Grass &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ice &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Fighting &#8594; Fairy/Steel = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Poison &#8594; Fairy/Steel = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Ground &#8594; Fairy/Steel = super-effective" class="type-fx-cell type-fx-200">2</td> <td title="Flying &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Psychic &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Bug &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-25">&frac14;</td> <td title="Rock &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Ghost &#8594; Fairy/Steel = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Dragon &#8594; Fairy/Steel = no effect" class="type-fx-cell type-fx-0">0</td> <td title="Dark &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> <td title="Steel &#8594; Fairy/Steel = normal effectiveness" class="type-fx-cell type-fx-100"></td> <td title="Fairy &#8594; Fairy/Steel = not very effective" class="type-fx-cell type-fx-50">&frac12;</td> </tr>
"""

soup = BeautifulSoup(html, 'html.parser')

# Extract all rows with Pokémon type combinations
rows = soup.find_all('tr', class_='has-pkmn')

# Prepare a dictionary to store type effectiveness vectors
type_effectiveness_vectors = {}

for row in rows:
    # Check if the div with class 'cell-dual-type' exists
    cell_dual_type = row.find('div', class_='cell-dual-type')
    if cell_dual_type:
        # Get the types
        types = cell_dual_type.find_all('a', class_='type-cell')
        if len(types) == 2:
            type1 = types[0].text.strip()
            type2 = types[1].text.strip()
        else:
            type1 = types[0].text.strip()
            type2 = None

        # Handle Normal/Null case
        if type2 == '—':
            type2 = None

        type_combination = f"{type1}/{type2}" if type2 else type1
        type_effectiveness_vectors[type_combination] = []

        # Get effectiveness against each type
        cells = row.find_all('td', class_='type-fx-cell')
        for cell in cells:
            title = cell['title']
            effectiveness_text = cell.get_text(strip=True)

            # Map textual representations to numerical values
            if effectiveness_text == '—':
                effectiveness = 1.0  # Normal effectiveness
            elif effectiveness_text == '½' or effectiveness_text == '½':
                effectiveness = 0.5  # Half effectiveness
            elif effectiveness_text == '2':
                effectiveness = 2.0  # Double effectiveness
            elif effectiveness_text == '¼' or effectiveness_text == '¼':
                effectiveness = 0.25  # Quarter effectiveness
            elif effectiveness_text == '4':
                effectiveness = 4.0  # Quadruple effectiveness
            elif effectiveness_text == '0':
                effectiveness = 0.0  # No effectiveness
            else:
                # If none of the above matches, default to 1.0 (normal effectiveness)
                effectiveness = 1.0

            # Store the effectiveness value
            effectiveness = float(effectiveness)  # Convert to float if needed
            type_effectiveness_vectors[type_combination].append(effectiveness)

# Prepare C++-compatible output
cpp_output = ""

# Generate code to initialize the vector of vectors
cpp_output += "std::vector<std::vector<float>> " + type1.lower() + "CombinedWeaknesses {\n"

for type_combo, effectiveness_vector in type_effectiveness_vectors.items():
    cpp_output += "    {"
    cpp_output += ", ".join([str(value) for value in effectiveness_vector])
    cpp_output += "}, // " + type_combo + "\n"
    
cpp_output += "};\n"

# Print the C++-formatted output
print(cpp_output)

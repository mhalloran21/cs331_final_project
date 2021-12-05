---
layout: page
title: Menu
---

<table class="table table-hover">
	<tr>
		<th>
			Item
		</th>
		<th>
			Description
		</th>
		<th>
			Price
		</th>
	</tr>
	{% for info in site.data.menu %}
	<tr>
	  <td>
	    {{ info.item }}
	  </td>
	  <td>
	    {{ info.description }}
	  </td>
	  <td>
	    {{ info.price | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>

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
	{% for info in site.data.lectures %}
	<tr>
	  <td>
	    {{ info.number }}
	  </td>
	  <td>
	    {{ info.date }}
	  </td>
	  <td>
	    {{ info.slides | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>

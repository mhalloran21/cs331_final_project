---
layout: page
title: Handouts
---

<table class="table table-hover">
	<tr>
		<th>
			Number
		</th>
		<th>
			Date
		</th>
		<th>
			Topic
		</th>
		<th>
			Handout
		</th>
	</tr>
	{% for info in site.data.handouts %}
	<tr>
	  <td>
	    {{ info.number }}
	  </td>
	  <td>
	    {{ info.date }}
	  </td>
	  <td>
	    {{ info.topic | newline_to_br }}
	  </td>
	  <td>
	    {{ info.handouts | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>

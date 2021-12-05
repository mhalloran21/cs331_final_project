---
layout: page
title: Readings
---

<table class="table table-hover">
	<tr>
		<th>
			Week
		</th>
		<th>
			Read By
		</th>
		<th>
			Reading
		</th>
		<th>
			Response Prompts
		</th>
	</tr>
	{% for info in site.data.readings %}
	<tr>
	  <td>
	    {{ info.week }}
	  </td>
	  <td>
	    {{ info.date }}
	  </td>
	  <td>
	    {{ info.reading | newline_to_br }}
	  </td>
	  <td>
	    {{ info.prompt | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>

---
layout: page
title: Lectures
---

<table class="table table-hover">
	<tr>
		<th>
			Lecture
		</th>
		<th>
			Date
		</th>
		<th>
			Topic
		</th>
		<th>
			Slides
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
	    {{ info.topic | newline_to_br }}
	  </td>
	  <td>
	    {{ info.slides | newline_to_br }}
	  </td>
	</tr>
	{% endfor %}
</table>

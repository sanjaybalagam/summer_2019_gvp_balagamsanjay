from django.shortcuts import *
from iplapp.models import *

def team_home_page(request,*args, **kwargs):
    year = [x for x in range(2008,2019)]
    teams= Matches.objects.values_list('team1').distinct();
    if kwargs:
        pass
    else:
        return render(request, 'team_home_page.html',context={'years': year,'teams':teams, })



from django.core.paginator import Paginator
from django.views import View
from django.shortcuts import *
from iplapp.models import *
from django.db.models import *
import operator


def pointstable(request, *args, **kwargs):
    if kwargs.get('year'):
        years = [i for i in range(2008, 2020)]
        match = Matches.objects.filter(season=kwargs.get('year')).values_list('winner').annotate(Count('winner')).order_by('-winner__count')
        return render(request,template_name='points_table.html',
                      context={
                          'teams':match,
                            'year':kwargs.get('year'),
                          'list':years,
                      })
    else:
        years = [i for i in range(2008, 2020)]
        match = Matches.objects.filter(season=2019).values_list('winner').annotate(
            Count('winner')).order_by('-winner__count')
        return render(request, template_name='points_table.html',
                      context={
                          'teams': match,
                          'year': kwargs.get('year'),
                          'list': years,
                      })


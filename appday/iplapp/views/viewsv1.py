from django.core.paginator import Paginator
from django.views import View
from django.shortcuts import *
from iplapp.models import *
import operator


def homepage(request, *args, **kwargs):
    years=[i for i in range(2008,2020)]
    isauth = request.user.is_authenticated
    if not isauth:
        return redirect('login')
    if kwargs:
        season=Matches.objects.filter(season= kwargs.get('year')).all()
        paginator = Paginator(season, 8)  # Show 25 contacts per page
        page = request.GET.get('page')
        seasons = paginator.get_page(page)
        return render(request, template_name='homepage.html', context={'list': years ,'seasons': seasons,
                                                                       'year':kwargs.get('year'),
                                                                       'isauth': isauth} )


    season = Matches.objects.filter(season=2019).all()
    paginator = Paginator(season, 8)  # Show 25 contacts per page
    page = request.GET.get('page')
    seasons = paginator.get_page(page)
    return render(request, template_name='homepage.html', context={'list': years, 'isauth': isauth,'seasons': seasons, 'year':'2019'})



def match_details(request, *args, **kwargs):
    match=Matches.objects.filter(matchid= kwargs.get('id')).all()
    details=Balls.objects.filter(match=match[0]).all()
    isauth = request.user.is_authenticated
    if not isauth:
        return redirect('login')
    team1 = [details[0].batting_team.lower(), {}, {}]
    team2 = [details[0].bowling_team.lower(), {}, {}]

    for i in details:
        if i.batting_team.lower() == team1[0]:
            if i.batsman.lower() not in team1[1]:
                team1[1][i.batsman.lower()] = i.batsman_runs
            else:
                team1[1][i.batsman.lower()] += i.batsman_runs
            if  i.dismissal_kind is not None:
                if i.bowler.lower() not in team1[2]:
                    team1[2][i.bowler.lower()] = 1
                else:
                    team1[2][i.bowler.lower()]+=1

        elif i.batting_team.lower() == team2[0]:
            if i.batsman.lower() not in team2[1]:
                team2[1][i.batsman.lower()] = i.batsman_runs
            else:
                team2[1][i.batsman.lower()] += i.batsman_runs
            if  i.dismissal_kind is not None:
                if i.bowler.lower() not in team2[2]:
                    team2[2][i.bowler.lower()] = 1
                else:
                    team2[2][i.bowler.lower()] += 1

    top_scorer_team1 = sorted(team1[1].items(), key=operator.itemgetter(1), reverse=True)[:3]
    top_bowler_team1 = sorted(team1[2].items(), key=operator.itemgetter(1), reverse=True)[:3]
    top_scorer_team2 = sorted(team2[1].items(), key=operator.itemgetter(1), reverse=True)[:3]
    top_bowler_team2 = sorted(team2[2].items(), key=operator.itemgetter(1), reverse=True)[:3]


    page = request.GET.get('page')

    innings1 = details.filter(inning=1)
    innings2 = details.filter(inning=2)
    if page is None:
        page="1"
    if page == "1":
        return render(request, template_name='pagelvl2.html', context={ 'match':match[0], 'innings1':innings1,"innings2": innings2,
                                                                        'number':1 ,
                                                                        'topscore_team1':top_scorer_team1,
                                                                        'topscore_team2':  top_scorer_team2 ,
                                                                        'team1': team1[0], 'team2':team2[0],
                                                                        'topbowlers1':top_bowler_team1,
                                                                        'topbowlers2':top_bowler_team2,
                                                                        'isauth':isauth})


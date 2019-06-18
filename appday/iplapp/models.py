from django.db import models

# Create your models here.


# class Seasons(models.Model):
#     seasonid=models.IntegerField()
#     matchid= models.IntegerField(unique=True)
#     year = models.CharField(('year'), choices=year_choices, default=current_year)
#
# class Teams(models.Model):
#     team_name= models.CharField(max_length=32)
#
# class Players(models.Model):
#     playername= models.CharField(max_length=32)
#
#
# class Umpire(models.Model):
#     Umpirename= models.CharField(max_length=32)
#
# class matches(models.Model):
#     matchid= models.ForeignKey(Seasons,to_field="matchid", db_column="matchid" )
#     team1= models.ForeignKey(Teams, on_delete=models.CASCADE)
#     team2= models.ForeignKey(Teams, on_delete=models.CASCADE)
#     toss_win= models.ForeignKey(Teams, on_delete=models.CASCADE)
#     result=models.BooleanField()
#     dl_applied = models.BooleanField()


class Matches(models.Model):
    matchid= models.IntegerField(unique=True)
    season = models.IntegerField()
    city= models.CharField(max_length=32, null=True)
    date=models.DateField(null=True)
    team1=models.CharField(max_length=32, null=True)
    team2=models.CharField(max_length=32, null=True)
    toss_winner= models.CharField(max_length=32, null=True)
    toss_decision=models.CharField(max_length=8, null=True)
    result=models.CharField(max_length=32, null=True)
    dl_applied= models.BooleanField()
    winner=models.CharField(max_length=32, null=True)
    win_by_runs=models.IntegerField()
    win_by_wickets=models.IntegerField()
    player_of_match=models.CharField(max_length=32, null=True)
    venue=models.CharField(max_length=100, null=True)
    umpire1=models.CharField(max_length=32, null=True)
    umpire2=models.CharField(max_length=32,null=True)
    umpire3=models.CharField(max_length=32, null=True)


class Balls(models.Model):
    match=models.ForeignKey(Matches,to_field="matchid",on_delete=models.CASCADE)
    inning=models.IntegerField()
    batting_team=models.CharField(max_length=32, null=True)
    bowling_team=models.CharField(max_length=32, null=True)
    over=models.IntegerField()
    ball=models.IntegerField()
    batsman=models.CharField(max_length=32, null=True)
    non_striker=models.CharField(max_length=32, null=True)
    bowler=models.CharField(max_length=32, null=True)
    is_super_over=models.BooleanField()
    wide_runs=models.IntegerField()
    bye_runs=models.IntegerField()
    legbye_runs=models.IntegerField()
    noball_runs=models.IntegerField()
    penalty_runs=models.IntegerField()
    batsman_runs=models.IntegerField()
    extra_runs=models.IntegerField()
    total_runs=models.IntegerField()
    player_dismissed=models.CharField(max_length=32, null=True)
    dismissal_kind=models.CharField(max_length=32, null=True)
    fielder=models.CharField(max_length=32, null=True)


import click
import string
import pdb

@click.group()
def strdemo():
    pass

@strdemo.command(help="secret function")
#@click.argument("username" , required=True)
@click.option("-u","--username",help="the name of the secret person", required=True , prompt=True)
@click.option("-p","--password",help="password",required=True, hide_input=True,prompt=True,confirmation_prompt=True )
def secret(username,password):
    click.echo(username)





if __name__ == '__main__':
    strdemo()
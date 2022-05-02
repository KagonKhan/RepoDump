from flask import Flask
from flask import render_template, request, redirect, url_for, flash, session
from flask import Flask, session
from flask_session import Session
from flask import g
import sqlite3

app = Flask(__name__)
wsgi_app = app.wsgi_app

sess = Session()
DATABASE = 'database.db'

# database stuff
def init_db():
    with app.app_context():
        db = get_db()
        with app.open_resource('schema.sql', mode='r') as f:
            db.cursor().executescript(f.read())
        db.commit()
def get_db():
    db = getattr(g, '_database', None)
    if db is None:
        db = g._database = sqlite3.connect(DATABASE)
    return db
@app.teardown_appcontext
def close_connection(exception):
    db = getattr(g, '_database', None)
    if db is not None:
        db.close()
def query_db(query, args=(), one=False):
    cur = get_db().execute(query, args)
    rv = cur.fetchall()
    cur.close()
    return (rv[0] if rv else None) if one else rv

def checkAdmin():
    if ( session['isAdmin'][0] is 1):
        return True
    else:
        return False


# This seems to be finished 
# /main_page or login_page
@app.route('/')
def index():  
    if not('user' in session):
        return render_template('login_page.html')

    books = query_db("select * from books")


    user = session['current_user']
    return render_template('index.html', books = books) + render_template('user_panel.html', currentPage = 'index', user = user)


# /users_page
@app.route('/users')
def users():
    if ( 'user' in session ):
        if not ( checkAdmin() ):
            return redirect(url_for('index'))

    users = query_db("select * from users")
    
    user = session['current_user']
    return render_template('users_page.html', users = users) + render_template('user_panel.html', currentPage = 'users', user = user)

# /users/user_page
@app.route('/users/<username>')
def profile(username):
    user = query_db("select * from users where username=(?)", [username])

    user_ = session['current_user']
    return render_template('user_page.html', user = user)+ render_template('user_panel.html', currentPage = 'user_page', user=user_)
# /users/user_page
@app.route('/users/<int:id>')
def user_by_id(id):
    #if not his page redirect
    if not(checkAdmin()):
        if not (id == session['current_user'][0]):
            return redirect(url_for('index'))

    user = query_db("select * from users where userID=(?)", [id])

    user_ = session['current_user']
    return render_template('user_page.html', user = user) + render_template('user_panel.html', currentPage = 'user_page', user=user_)
 

# add a user
@app.route('/users', methods=['POST'])
def add_user():
    if ( 'user' in session ):
        if not ( checkAdmin() ):
            return redirect(url_for('index'))

    login    = request.form['login']
    password = request.form['password']
    isAdmin  = False
    if ( request.form.get('admin') ):
        isAdmin = True;

    query_db("INSERT INTO users (username, password, isAdmin) VALUES (?,?,?)", [login, password, isAdmin])
    get_db().commit()
    return users()

# add a book
@app.route('/', methods=['POST'])
def add_book():
    title = request.form['title']

    query_db("INSERT INTO books (title) VALUES (?)", [title])
    get_db().commit()
    flash('Added a book!')

    return index();


# login
@app.route('/login', methods = ['POST'])
def login():
    username = request.form['login']
    user_pass = request.form['password']

    result = query_db('SELECT * FROM users WHERE username = (?) AND password = (?)', [username, user_pass], one=True)
    if ( result is not None ):
        session['user'] = username
        session['current_user'] = result
        session['isAdmin'] = query_db('SELECT isAdmin FROM users WHERE username = (?) AND password = (?)', [username, user_pass], one=True)
        flash('Logged in!')
        return redirect(url_for('index'))
    else:
        flash('Incorrect login!')
        return index()

    

# /logout
@app.route('/logout')
def logout():
    if( 'user' in session ):
        session.pop('user')
    else:
        redirect(url_for('index'))
    
    flash('Logged out!')
    return redirect(url_for('index'))


if __name__ == '__main__':
    import os
    HOST = os.environ.get('SERVER_HOST', 'localhost')
    try:
        PORT = int(os.environ.get('SERVER_PORT', '5555'))
    except ValueError:
        PORT = 5555

   
    app.secret_key = '12345678'
    app.config['SESSION_TYPE'] = 'filesystem'
    sess.init_app(app)
    app.config.from_object(__name__)
   # init_db()
    app.run(HOST, PORT)

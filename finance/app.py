import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from dotenv import load_dotenv

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
load_dotenv()
if not os.getenv("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    return render_template("portfolio.html",cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    
    if request.method == "POST":
        #Get data
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")
        
        res = lookup(symbol)
        #Find total price of shares and round it to 2 decimal places
        
        #Result can return None. Handle it here.
        if not res:
            return apology("Invalid symbol!", 400)
        
        #If shares is negative or not a string number, thats not possible
        if int(shares) < 0 or not shares.isdigit():
            return apology("Invalid number of shares!", 400)

        userCash = db.execute("SELECT cash FROM users WHERE username = ?", session["user_id"])
        print(f"{userCash=}")
        # return redirect("/")
        
        if not shares.isdigit():
            return apology("Invalid number of shares!", 400)

        #If shares is negative, thats not possible
        if int(shares) < 0:
            return apology("Invalid number of shares!", 400)

        multiple = True if int(shares) > 1 else False
        total = usd(res["price"] * int(shares))
        # select the ammount of cash the user has
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        return redirect("/")
        # return render_template("bought.html",shares=shares,symbol=res["symbol"],price=res["price"],total=total,multiple=multiple,name=res["name"])


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "GET":
        return render_template("quote.html")
    
    #Look up symbol
    if request.method == "POST":
        symbol = request.form.get("symbol")
        res = lookup(symbol)
        
        #Result can return None. Handle it here.
        if not res:
            return apology("Invalid symbol!", 400)
        #If result found, render the template with new information
        return render_template("quoted.html", name=res["name"],price=usd(res["price"]),symbol=res["symbol"])
    


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    
    #Get username and password to enter into 
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirm = request.form.get("confirm")

        if username == "" or len(db.execute('SELECT username FROM users WHERE username = ?', username)) > 0:
            return apology("Invalid username. Please try again!",400)

        if password == "" or password != confirm:
            return apology("Invalid Password. Please try again!",400)
        
        db.execute('INSERT INTO users (username, hash) \
            VALUES(?, ?)', username, generate_password_hash(password))

        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        
        # Log user in, i.e. Remember that this user has logged in
        session["user_id"] = rows[0]["id"]
        # Redirect user to home page
        return redirect("/")
        

    


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")

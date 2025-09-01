import sqlite3
import requests

def openinformation(name, code):
    connection = sqlite3.connect("data/open.db")
    cursor = connection.cursor()

    response = requests.get("http://worldtimeapi.org/api/timezone/Asia/Yerevan")
    data = response.json()

    datetime = data["datetime"][:16]

    cursor.execute("INSERT INTO open (name, code, time) VALUES (?,?,?)", (name, code, datetime))

    connection.commit()
    connection.close()

def creatdocument():
    connection = sqlite3.connect("data/open.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM open")
    rows = cursor.fetchall()

    if(rows != []):
        with open('data/infromation.txt', 'w') as file:
            for row in rows:
                file.write(str(row) + '\n')
        return True
    else:
        return False

    connection.commit()
    connection.close()

def cleanopeninformation():
    connection = sqlite3.connect('data/open.db')
    cursor = connection.cursor()

    cursor.execute("DELETE FROM open")

    connection.commit()
    connection.close()

def checkId(id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM users WHERE id = ?", (id,))
    user = cursor.fetchone()

    if not user:
        return False
    else:
        return True

    connection.commit()
    connection.close()

def checkRole(id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM users WHERE id = ?", (id,))
    role = cursor.fetchone()

    if role[0] == "admin":
        return True
    else:
        return False

    connection.commit()
    connection.close()

def users():
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM users")
    array = cursor.fetchall()
    return array

    connection.commit()
    connection.close()

def changeAdmin(id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("UPDATE users SET role = ? WHERE role = ?", ("user", "admin"))
    cursor.execute("UPDATE users SET role = ? WHERE id = ?", ("admin", id))

    connection.commit()
    connection.close()


def addUser(id, firstname):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("INSERT INTO users (role, id, codeLength, firstname) VALUES (?,?,?,?)", ("user", id, 4, firstname))

    connection.commit()
    connection.close()

def deleteUser(id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("DELETE FROM users WHERE id = ?", (id,))

    connection.commit()
    connection.close()

def codeLengthUpdate(codeLenght, id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("UPDATE users SET codeLength = ? WHERE id = ?", (codeLenght, id))

    connection.commit()
    connection.close()

def saveCodeLength(id):
    connection = sqlite3.connect("data/userdatabase.db")
    cursor = connection.cursor()

    cursor.execute("SELECT * FROM users WHERE id = ?", (id,))
    length = cursor.fetchone()
    return length[2]

    connection.commit()
    connection.close()

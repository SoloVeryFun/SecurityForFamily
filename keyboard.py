from aiogram.utils.keyboard import ReplyKeyboardBuilder
from aiogram.types import ReplyKeyboardMarkup, KeyboardButton

items = [
        "4", "5", "6"
    ]

admin = [
    "Chenge Admin", "Users", "Add user", "Delete user", "Open information", "Clean open information", "EXIT"
]

cancel = ReplyKeyboardMarkup(
    keyboard=[
        [KeyboardButton(text="cancel")]
    ],
    resize_keyboard=True
)

def admincommands():
    builder = ReplyKeyboardBuilder()
    [builder.button(text=item) for item in admin]
    builder.adjust(2,2,2,1)
    return builder.as_markup(resize_keyboard=True)

def changeLength():
    builder = ReplyKeyboardBuilder()
    [builder.button(text=item) for item in items]
    builder.button(text="cancel")
    builder.adjust(3,1)
    return builder.as_markup(resize_keyboard=True)
import asyncio
import time
import serial
import send
import userDataBase
from aiogram import Bot, Dispatcher, Router, F
from aiogram.types import Message
from aiogram.filters import CommandStart, Command
from aiogram.fsm.context import FSMContext
from aiogram.fsm.state import StatesGroup, State

API_TOKEN = "7955511531:AAEKyQG2vzF_qxYhx8QaFo_JyMtJni63PwA"
bot = Bot(token=API_TOKEN)
router = Router()

# Переменные
incorrectid = "Вы ввели неправильный ID, пожалуйста, проверьте"
notauthorized = "Вы не имеете права использовать замок, пожалуйста, обратитесь к владельцу за разрешением"
ARDUINO_PORT = 'COM3'  # Установите правильный COM-порт для вашего Arduino

# Функция для отправки данных на Arduino
def send_data_to_arduino(key: str, code: str):
    try:
        with serial.Serial(ARDUINO_PORT, 9600, timeout=1) as ser:  # Установите правильный COM-порт и скорость
            time.sleep(2)  # Ждем, пока Arduino загрузится
            # Отправка ключа и кода
            ser.write((key + '\n').encode())
            time.sleep(0.1)  # Небольшая задержка
            ser.write((code + '\n').encode())
    except Exception as e:
        print(f"Ошибка при отправке данных на Arduino: {e}")

@router.message(Command("start"))
async def start(message: Message):
    await message.answer("Добро пожаловать! Используйте /open для открытия замка.")

@router.message(Command("open"))
async def open(message: Message):
    if userDataBase.checkId(message.chat.id):
        code = send.open(message.chat.id)
        await message.answer(text=code)
        userinfo = await bot.get_chat_member(user_id=message.chat.id, chat_id=message.chat.id)
        name = userinfo.user.first_name
        userDataBase.openinformation(name, code)

        # Отправка данных на Arduino
        send_data_to_arduino(name, code)  # Отправляем ключ и код на Arduino
    else:
        await message.answer(notauthorized)

@router.message(Command("info"))
async def info(message: Message):
    await message.answer("Используйте команды: /open для открытия замка.")

if __name__ == '__main__':
    # Создаем экземпляр диспетчера и запускаем бота
    dp = Dispatcher()
    dp.include_router(router)

    asyncio.run(dp.start_polling(bot))

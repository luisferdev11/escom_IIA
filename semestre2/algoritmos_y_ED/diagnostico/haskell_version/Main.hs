import Control.Monad (forever, when)
import Data.IORef
import Data.List (delete)
import System.Exit (exitSuccess)

data Pelota = Pelota { alto :: Int, ancho :: Int, color :: String }
  deriving (Eq, Show)

crearPelota :: IO Pelota
crearPelota = do
  putStrLn "Introduce el alto:"
  altoStr <- getLine
  let alto = read altoStr :: Int

  putStrLn "Introduce el ancho:"
  anchoStr <- getLine
  let ancho = read anchoStr :: Int

  putStrLn "Introduce el color:"
  color <- getLine

  return $ Pelota alto ancho color

mostrarPelotas :: [Pelota] -> IO ()
mostrarPelotas pelotas = mapM_ (putStrLn . show) pelotas

main :: IO ()
main = do
  -- Variable para almacenar pelotas (en una lista mutable)
  pelotas <- newIORef []

  -- Menú de operaciones
  forever $ do
    putStrLn "1. Crear pelota"
    putStrLn "2. Destruir pelota"
    putStrLn "3. Mostrar pelotas"
    putStrLn "4. Salir"

    opcion <- getLine

    case opcion of
      "1" -> do
        pelota <- crearPelota
        modifyIORef pelotas (pelota:)
      "2" -> do
        putStrLn "Introduce el índice de la pelota a destruir:"
        indiceStr <- getLine
        let indice = read indiceStr :: Int

        pelotasActuales <- readIORef pelotas
        when (indice >= 1 && indice <= length pelotasActuales) $ do
          modifyIORef pelotas (delete $ pelotasActuales !! (indice - 1))
      "3" -> do
        pelotasActuales <- readIORef pelotas
        mostrarPelotas pelotasActuales
      "4" -> exitSuccess
      _  -> putStrLn "Opción no válida."

import { configureStore } from '@reduxjs/toolkit';
import graphSliceReducer from './graphSlice';

export const store = configureStore({
  reducer: {
    graph: graphSliceReducer,
  },
});

export type AppDispatch = typeof store.dispatch;
export type RootState = ReturnType<typeof store.getState>;

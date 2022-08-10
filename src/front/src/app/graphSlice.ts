import { createSlice } from '@reduxjs/toolkit'

const initialState = {
    settings: {
        x: 0,
        x_min: -20,
        x_max: 20,
        y_min: -5,
        y_max: 5,
        func: 'sin(x)'
    },
    points: [[0,0]]
}

export const graphSlice = createSlice({
    name: 'graph',
    initialState,
    reducers: {
        getInput: (state, action) => {
            state.settings.x = action.payload.x;
            state.settings.x_min = action.payload.x_min;
            state.settings.x_max = action.payload.x_max;
            state.settings.y_min = action.payload.y_min;
            state.settings.y_max = action.payload.y_max;
        },
        addGraphSeries: (state, action) => {

        }
    }
})

export const {getInput, addGraphSeries} = graphSlice.actions;
export default graphSlice.reducer;